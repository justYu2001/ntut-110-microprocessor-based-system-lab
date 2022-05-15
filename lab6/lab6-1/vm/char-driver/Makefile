obj-m := demo.o
kernel_DIR := /usr/src/linux-headers-5.4.0-109-generic/
PWD := $(shell pwd)

all:
	gcc -o test.o test.c
	make -C $(kernel_DIR) M=$(PWD)

clean:
	rm *.o *.ko *.mod.c

.PHONY:
	clean