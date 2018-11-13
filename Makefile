MY_TARGET := sread.ko
obj-m := sread.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
MODULE_DIR := /lib/modules/$(shell uname -r)/kernel/sread
PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
install :
	mkdir -p $ $(MODULE_DIR)
	cp -f $(MY_TARGET) $(DODULE_DIR)
clean :
	$(MAKE) -C $(KERNEL_DIR_ SUBDIRS=$(PWD) clean
