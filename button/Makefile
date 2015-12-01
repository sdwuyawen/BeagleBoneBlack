KERN_DIR = /home/wu/workspace/kernel/linux
CROSS_COMPILE = arm-linux-gnueabihf-

obj-m	+= button.o

all:
		make -C $(KERN_DIR) M=`pwd` modules ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE)

clean:
		make -C $(KERN_DIR) M=`pwd` modules clean ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE)
			rm -rf modules.order

