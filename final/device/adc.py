import random
from config import settings

spiClock = 11
spiMiso = 9
spiMosi = 10
spiCs = 8
photoCh = 0

def initialize_adc_sensor():
    import Jetson.GPIO as gpio
    gpio.setwarnings(False)
    gpio.cleanup()
    gpio.setmode(gpio.BCM)
    gpio.setup(spiMosi, gpio.OUT)
    gpio.setup(spiMiso, gpio.IN)
    gpio.setup(spiClock, gpio.OUT)
    gpio.setup(spiCs, gpio.OUT)
    
def get_adc_value():
    if settings.mode == "development":
        return random.uniform(-1000, 2000)
    
    import Jetson.GPIO as gpio
    
    if photoCh > 7 or photoCh < 0 :
        return -1

    gpio.output(spiCs, True)

    gpio.output(spiClock, False)
    gpio.output(spiCs, False)

    commandOut = photoCh
    commandOut |= 0x18
    commandOut <<= 3

    for i in range(5):
        if commandOut & 0x80:
            gpio.output(spiMosi, True)
        else:
            gpio.output(spiMosi, False)

        commandOut <<= 1
        gpio.output(spiClock, True)
        gpio.output(spiClock, False)

    abcOut = 0

    for i in range(12):
        gpio.output(spiClock, True)
        gpio.output(spiClock, False)
        abcOut <<= 1
        if gpio.input(spiMiso):
            abcOut |= 0x1

    gpio.output(spiCs, True)

    abcOut >>= 1
    return abcOut