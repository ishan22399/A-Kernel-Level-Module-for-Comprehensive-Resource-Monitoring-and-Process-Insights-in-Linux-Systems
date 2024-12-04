# Makefile for building the custom_monitor kernel module

# Specify the name of the module to be built
obj-m += tony.o

# Kernel build directory
KDIR := /lib/modules/$(shell uname -r)/build

# Current directory
PWD := $(shell pwd)

# Default target for building the kernel module
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Clean target to remove built files
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

