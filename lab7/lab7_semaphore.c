#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "gpio.h"

sem_t semaphore;

int gpioPin[4] = { 396, 392, 481, 388 };
char statusList[5];
char negativeList[5];
int times;

void* ledOneHandler() {
    int gpio = 396;
    int value = statusList[0] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        if (i % 2 == 0) {
            printf("Status: %s\n", statusList);
        } else {
            printf("Status: %s\n", negativeList);
        }
        setValue(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sem_post(&semaphore);
    }

    pthread_exit(NULL);
}

void* ledTwoHandler() {
    int gpio = 392;
    int value = statusList[1] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        setValue(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sem_post(&semaphore);
    }

    pthread_exit(NULL);
}

void* ledThreeHandler() {
    int gpio = 481;
    int value = statusList[2] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        setValue(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sem_post(&semaphore);
    }

    pthread_exit(NULL);
}

void* ledFourHandler() {
    int gpio = 388;
    int value = statusList[3] - '0';
    for (int i = 0; i < times * 2; i++) {
        sem_wait(&semaphore);
        setValue(gpio, value);
        printf("GPIO: %d status: %d\n", gpio, value);
        value = (value + 1) % 2;
        sem_post(&semaphore);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("argc number error\n");
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        statusList[i] = argv[1][i];
        negativeList[i] = statusList[i] == '0' ? '1' : '0';
    }

    times = argv[2][0] - '0';

    for (int i = 0; i < 4; i++) {
        exportGpio(gpioPin[i]);
        setDirection(gpioPin[i], 1);
        setValue(gpioPin[i], 0);
    }

    sem_init(&semaphore, 0, 1);

    pthread_t pthreadList[4];
    pthread_create(&pthreadList[0], NULL, ledOneHandler, NULL);
    usleep(100);
    pthread_create(&pthreadList[1], NULL, ledTwoHandler, NULL);
    usleep(100);
    pthread_create(&pthreadList[2], NULL, ledThreeHandler, NULL);
    usleep(100);
    pthread_create(&pthreadList[3], NULL, ledFourHandler, NULL);

    for (int i = 0; i < 4; i++) {
        setValue(gpioPin[i], 0);
        unexportGpio(gpioPin[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(pthreadList[i], NULL);
    }

    return 0;
}