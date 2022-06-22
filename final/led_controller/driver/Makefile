obj-m := final_driver.o

ifeq ($(KERNELDIR),)
KERNELDIR=/lib/modules/$(shell uname -r)/build
endif

all:
	g++ -o controller controller.cpp
	make -C $(KERNELDIR) SUBDIRS=$(PWD) modules
    
clean:
	rm -f *.ko *.mod.c modules.* *.o