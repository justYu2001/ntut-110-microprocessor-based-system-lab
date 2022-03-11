#include <fstream>
#include <string>
#include <cerrno>

using namespace std;

void setExport(unsigned int gpio) {
	ofstream outFileStream;

	outFileStream.open("/sys/class/gpio/export");

	if(!outFileStream.is_open()) {
		perror("failed to open export");
		return;
	} else {
		outFileStream << gpio;
		outFileStream.close();
	}
}

void setUnexport(unsigned int gpio) {
	ofstream outFileStream;

	outFileStream.open("/sys/class/gpio/unexport");

	if(!outFileStream.is_open()) {
		perror("failed to open unexport");
		return;
	} else {
		outFileStream << gpio;
		outFileStream.close();
	}
}

void setDirection(unsigned int gpio, string direction) {
	ofstream outFileStream;

	outFileStream.open("/sys/class/gpio/gpio" + to_string(gpio) + "/direction");

	if(!outFileStream.is_open()) {
		perror("failed to open direction");
		return;
	} else {
		outFileStream << direction;
		outFileStream.close();
	}
}

void setValue(unsigned int gpio, int value) {
	ofstream outFileStream;

	outFileStream.open("/sys/class/gpio/gpio" + to_string(gpio) + "/value");

	if(!outFileStream.is_open()) {
		perror("failed to open value");
		return;
	} else {
		outFileStream << value;
		outFileStream.close();
	}
}

int main(int argc, char *argv[]) {
    int leds[4] = {396, 466, 392, 481};

    char *led = argv[1];
    char *value = argv[2];

    for (int i = 0; i < 4; i++) {
        if (led[3] - '0' == i) {
	    	if (value[1] == 'n') {
				setExport(leds[i]);
				setDirection(leds[i], "out");
				setValue(leds[i], 1);
			} else {
				setValue(leds[i], 0);
				setUnexport(leds[i]);
			}
			break;
		}
    }

    return 0;
}
