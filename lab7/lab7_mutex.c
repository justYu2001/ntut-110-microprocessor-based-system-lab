#include <stdio.h>
#include <pthread.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

pthread_mutex_t mutex;

int gpioPin[4] = { 396, 392, 481, 388 };
char statusList[5];
char negativeList[5];
int times;

void* ledOneHandler() {
    int gpio = 396;
    int value = statusList[0] - '0';
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        if (i % 2 == 0) {
            printf("Status: %s\n", statusList);
        } else {
            printf("Status: %s\n", negativeList);
        }
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d", gpio, value);
        value = (value + 1) % 2;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    
    pthread_exit(NULL);
}

void* ledTwoHandler() {
    int gpio = 392;
    int value = statusList[1] - '0';
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d", gpio, value);
        value = (value + 1) % 2;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_exit(NULL);
}

void* ledThreeHandler() {
    int gpio = 481;
    int value = statusList[2] - '0';
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d", gpio, value);
        value = (value + 1) % 2;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_exit(NULL);
}

void* ledFourHandler() {
    int gpio = 388;
    int value = statusList[3] - '0';
    for (int i = 0; i < times * 2; i++) {
        pthread_mutex_lock(&mutex);
        gpio_set_value(gpio, value);
        printf("GPIO: %d status: %d", gpio, value);
        value = (value + 1) % 2;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("argc number error\n");
        return 0;
    }

    statusList = argv[0];

    for (int i = 0; i < 4; i++) {
        negativeList[i] = statusList[i] == '0' ? '1' : '0';
    }

    times = argv[1][0] - '0';
    
    char* ledName[4] = { "LED1", "LED2", "LED3", "LED4" };

    for (int i = 0; i < 4; i++) {
        if (gpio_is_valid(gpioPin[i]) == 0) {
            printk("pin %d is no valid\n", gpioPin[i]);
            return -EBUSY;
        }

        if (gpio_request(gpioPin[i], ledName[i]) < 0) {
            printk("pin %d is busy\n", gpioPin[i]);
            return -EBUSY;
        }

        gpio_direction_output(gpioPin[i], 0);
        gpio_export(gpioPin[i], false);
    }

    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, 0);

    pthread_t pthreadList[4];
    pthread_create(&pthreadList[0], NULL, ledOneHandler, NULL);
    pthread_create(&pthreadList[1], NULL, ledTwoHandler, NULL);
    pthread_create(&pthreadList[2], NULL, ledThreeHandler, NULL);
    pthread_create(&pthreadList[3], NULL, ledFourHandler, NULL);

    for (int i = 0; i < 4; i++) {
        pthread_join(pthreadList[i], NULL);
    }

    for (int i = 0; i < 4; i++) {
        gpio_set_value(gpioPin[i], 0);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}