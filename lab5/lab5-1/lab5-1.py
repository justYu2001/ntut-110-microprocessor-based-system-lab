import Jetson.GPIO as gpio
import time

spiClock = 11
spiMiso = 9
spiMosi = 10
spiCs = 8

led1 = 21
led2 = 13

photoCh = 0

def init():
    gpio.setwarnings(False)
    gpio.cleanup()
    gpio.setmode(gpio.BCM)
    gpio.setup(spiMosi, gpio.OUT)
    gpio.setup(spiMiso, gpio.IN)
    gpio.setup(spiClock, gpio.OUT)
    gpio.setup(spiCs, gpio.OUT)
    gpio.setup([led1, led2], gpio.OUT, initial = gpio.LOW)

def readAdc(adcNum, clockPin, mosiPin, misoPin, csPin):
    if adcNum > 7 or adcNum < 0 :
        return -1

    gpio.output(csPin, True)

    gpio.output(clockPin, False)
    gpio.output(csPin, False)

    commandOut = adcNum
    commandOut |= 0x18
    commandOut <<= 3

    for i in range(5):
        if commandOut & 0x80:
            gpio.output(mosiPin, True)
        else:
            gpio.output(mosiPin, False)

        commandOut <<= 1
        gpio.output(clockPin, True)
        gpio.output(clockPin, False)

    abcOut = 0

    for i in range(12):
        gpio.output(clockPin, True)
        gpio.output(clockPin, False)
        abcOut <<= 1
        if gpio.input(misoPin):
            abcOut |= 0x1

    gpio.output(csPin, True)

    abcOut >>= 1
    return abcOut

def main():
    init()
    while True:
        adcValue = readAdc(photoCh, spiClock, spiMosi, spiMiso, spiCs)
        print(adcValue)

        if adcValue > 600:
            gpio.output([led1, led2], (gpio.HIGH, gpio.HIGH))
            print('led1: on, led2:on')
        
        elif adcValue > 200:
            gpio.output([led1, led2], (gpio.HIGH, gpio.LOW))
            print('led1: on, led2:off')

        else:
            gpio.output([led1, led2], (gpio.LOW, gpio.LOW))
            print('led1: off, led2:off')

        time.sleep(1)

main()