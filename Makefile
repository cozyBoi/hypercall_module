obj-m += hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#	make -C $(KDIR) SUBDIR=$(PWD) modules
#	make -C $(KDIR) M=$PWD

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#	rm -rf *.o *.ko *.mod.* *.symvers *.order
	
