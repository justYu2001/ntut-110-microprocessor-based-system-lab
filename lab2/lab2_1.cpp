#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[]) {
    int leds[4] = {396, 466, 392, 481};

    char *led = argv[1];
    char *value = argv[2];

    for (int i = 0; i < 4; i++) {
        if (led[3] - '0' == i) {
	    if (value[1] == 'n') {
	        gpio_export(leds[i]);
		gpio_set_dir(leds[i], "out");
		gpio_set_value(leds[i], 1);
	    } else {
	        gpio_set_value(leds[i], 0);
		gpio_unexport(leds[i]);
	    }
	    break;
	}
    }

    return 0;
}
