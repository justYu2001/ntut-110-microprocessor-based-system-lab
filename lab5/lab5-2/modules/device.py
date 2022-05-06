import Jetson.GPIO as gpio
import asyncio

class Device:
    def __init__(self):
        self.spiClock = 11
        self.spiMiso = 9
        self.spiMosi = 10
        self.spiCs = 8

        # 7, 12
        self.leds = [4, 18]
        self.stateList = [False, False]


        self.isChanged = False

        self.photoCh = 0

        gpio.setwarnings(False)
        gpio.cleanup()
        gpio.setmode(gpio.BCM)
        gpio.setup(self.spiMosi, gpio.OUT)
        gpio.setup(self.spiMiso, gpio.IN)
        gpio.setup(self.spiClock, gpio.OUT)
        gpio.setup(self.spiCs, gpio.OUT)
        gpio.setup(self.leds, gpio.OUT, initial = gpio.LOW)

    def getADCValue(self):       
        if self.photoCh > 7 or self.photoCh < 0 :
            return -1

        gpio.output(self.spiCs, True)
        gpio.output(self.spiClock, False)
        gpio.output(self.spiCs, False)

        commandOut = self.photoCh
        commandOut |= 0x18
        commandOut <<= 3

        for i in range(5):
            if commandOut & 0x80:
                gpio.output(self.spiMosi, True)
            else:
                gpio.output(self.spiMosi, False)

            commandOut <<= 1
            gpio.output(self.spiClock, True)
            gpio.output(self.spiClock, False)

        abcOut = 0

        for i in range(12):
            gpio.output(self.spiClock, True)
            gpio.output(self.spiClock, False)
            abcOut <<= 1
            if gpio.input(self.spiMiso):
                abcOut |= 0x1

        gpio.output(self.spiCs, True)

        abcOut >>= 1
        return abcOut

    def setAllLedState(self, stateList):
        toGPIOState = lambda state: gpio.HIGH if state else gpio.LOW
        gpioStateList = map(toGPIOState, stateList)
        gpio.output(self.leds, tuple(gpioStateList))
        self.stateList = stateList
        self.isChanged = True

    async def shine(self, times):
        for i in range(times):
            self.setAllLedState([True, False])
            await asyncio.sleep(0.8)
            self.setAllLedState([False, True])
            await asyncio.sleep(0.8)
        
        self.setAllLedState([False, False])

    async def onLedStateChange(self, callback):
        if self.isChanged:
            self.isChanged = False
            await callback(self.ledStateList)
        else:
            await asyncio.sleep(0)