#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

void exportGpio(unsigned int gpio) {
    int fd, len;
	char buf[MAX_BUF];
 
	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return;
	}
 
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);
}

void unexportGpio(unsigned int gpio) {
    int fd, len;
	char buf[MAX_BUF];
 
	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return;
	}
 
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);
}

void setDirection(unsigned int gpio, unsigned int direction) {
    int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
 
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/direction");
		return;
	}
 
	if (direction) write(fd, "out", 4);
	else write(fd, "in", 3);
 
	close(fd);
}

void setValue(unsigned int gpio, unsigned int value) {
    int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return;
	}
 
	if (value) write(fd, "1", 2);
	else write(fd, "0", 2);
 
	close(fd);
}

int isBusyGpioPin(unsigned int gpio) {
	char buf[MAX_BUF];
 
	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d", gpio);

	DIR* dir = opendir(buf);
	if (dir) {
		closedir(dir);
		return 1;
	} else {
		return 0;
	}
}