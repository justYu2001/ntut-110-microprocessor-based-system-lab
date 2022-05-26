#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_MAJOR 60
#define DRIVER_NAME "demo"

int gpioPin[4] = { 396, 392, 481, 398 };
int ledPin[4] = { 7, 12, 18, 29 };
int ledBook[4] = { 0, 0, 0, 0 };
static char userChar[100];

static int driver_open(struct inode *inode, struct file *filp) {
    printk("Open: Enter Open function\n");
    return 0;
}

static int driver_close(struct inode *inode, struct file *filp) {
    printk("Release: Enter Release function\n");
    return 0;
}

long driver_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("I/O Control: Enter I/O Control function\n");
    return 0;
}

static ssize_t driver_read(struct file *filp, char *buf, size_t size, loff_t *f_pos) {
    printk("Read: Enter Release function\n");
    return 0;
}

static ssize_t driver_write(struct file *filp, const char *buf, size_t size, loff_t *f_pos) {
    printk("Write: Enter Write function\n");
    if(copy_from_user(userChar, buf, size) == 0){
        userChar[size - 1] = '\0';
        printk("userChar:%s\n", userChar);

        int ledIndex = userChar[size - 2] - '1';

        if(userChar[0] == 'g') {
            printk("LED%d Status: %d\n", ledIndex + 1, ledBook[ledIndex]);
        } else if (userChar[1] == 'n') {
            gpio_direction_output(ledPin[ledIndex], 1);
            ledBook[ledIndex] = 1;
        } else if (userChar[1] == 'f') {
            gpio_set_value(ledPin[ledIndex], 0);
            gpio_free(ledPin[ledIndex]);
            ledBook[ledIndex] = 0;
        } else {
            printk("Error: command not found");
        }
    } else{
        printk("Error: Write Error\n");
    }
    return size;
}

static struct file_operations driver_fops = {
    .open = driver_open,
    .release = driver_close,
    .unlocked_ioctl = driver_ioctl,
    .read = driver_read,
    .write = driver_write,
};

static int driver_init(void) {
    int result;
    printk("<1>demo: started\n");

    /* Register character device */
    result = register_chrdev(DRIVER_MAJOR, DRIVER_NAME, &driver_fops);
    if (result < 0) {
        printk("<1>demo: Failed to register character device\n");
        return result;
    }

    return 0;
}

static void driver_exit(void) {
    printk("<1>demo: removed\n");

    /* Unregister character device */
    unregister_chrdev(DRIVER_MAJOR, DRIVER_NAME);
}

module_init(driver_init);
module_exit(driver_exit);
