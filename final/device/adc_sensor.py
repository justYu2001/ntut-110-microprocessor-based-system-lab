import random
from config import settings

class ADCSensor:
    def __init__(self):
        self.spiClock = 11
        self.spiMiso = 9
        self.spiMosi = 10
        self.spiCs = 8
        self.photoCh = 0

        if settings.mode == "production":
            import Jetson.GPIO as gpio
            gpio.setwarnings(False)
            gpio.cleanup()
            gpio.setmode(gpio.BCM)
            gpio.setup(self.spiMosi, gpio.OUT)
            gpio.setup(self.spiMiso, gpio.IN)
            gpio.setup(self.spiClock, gpio.OUT)
            gpio.setup(self.spiCs, gpio.OUT)
    
    def get_value(self):
        if settings.mode == "development":
            return random.uniform(-3000, 2000)
        
        import Jetson.GPIO as gpio
        
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

ADC_Sensor = ADCSensor()