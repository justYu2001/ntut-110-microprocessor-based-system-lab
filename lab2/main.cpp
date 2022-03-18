#include <string>
#include <cerrno>
#include <chrono>
#include <thread>
#include <iostream>
#include "gpio.h"

using namespace std;

void turnOnLED(unsigned int gpio) {
    setExport(gpio);
    setDirection(gpio, "out");
    setValue(gpio, 1);
    setUnexport(gpio);
}

void turnOffLED(unsigned int gpio) {
        setUnexport(gpio);
        setExport(gpio);
setDirection(gpio, "out");
    setValue(gpio, 0);
    setUnexport(gpio);
}

int leds[4] = {396, 392, 481, 398};

void switchLED(string led, string status) {
    int ledID = led[3] - '1';
    for (int i = 0; i < 4; i++) {
        if (ledID == i) {
            if (status == "on") {
                turnOnLED(leds[i]);
            } else {
                turnOffLED(leds[i]);
            }
            return;
        }
    }
}

void flashLED(int times) {
    for(int i = 0; i < times; i++) {
        turnOnLED(leds[0]);
        turnOnLED(leds[1]);
        turnOffLED(leds[2]);
        turnOffLED(leds[3]);
        this_thread::sleep_for(chrono::seconds(1));
        turnOnLED(leds[3]);
        turnOnLED(leds[2]);
        turnOffLED(leds[1]);
        turnOffLED(leds[0]);
        this_thread::sleep_for(chrono::seconds(1));
    }
    turnOffLED(leds[2]);
        turnOffLED(leds[3]);
}

int main(int argc, char *argv[]) {
    string firstArgument(argv[1]);
    string secondArgument(argv[2]);

    cout << firstArgument << endl;
    cout << secondArgument << endl;
    if(firstArgument.substr(0, 3) == "LED") {
        switchLED(firstArgument, secondArgument);
    } else if (firstArgument.substr(0, 10) == "Mode_Shine") {
        int times = stoi(secondArgument);
        flashLED(times);
    } else {
        perror("command not found");
    }

    return 0;
}