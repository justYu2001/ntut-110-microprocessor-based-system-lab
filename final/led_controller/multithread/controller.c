#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "gpio.h"

sem_t semaphore;

int gpioPin = 466;
int LEDStatus = 0;

void* ledHandler() {
    sem_wait(&semaphore);
    setValue(gpioPin, LEDStatus);
    if (LEDStatus == 0) {
        unexportGpio(gpioPin);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("argc number error\n");
        return 0;
    }

    if (argv[1][1] == 'n') {
        LEDStatus = 1;
    } else if (argv[1][1] == 'f') {
        LEDStatus = 0;
    }

    if(isBusyGpioPin(gpioPin) == 0) {
        exportGpio(gpioPin);
        setDirection(gpioPin, 1);
    }

    sem_init(&semaphore, 0, 0);

    pthread_t pthreadList[4];
    pthread_create(&pthreadList[0], NULL, ledHandler, NULL);
    pthread_join(pthreadList[i], NULL);

    return 0;
}