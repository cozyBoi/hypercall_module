obj-m += hello.o

KDIR =~/rpmbuild/BUILD/kernel-3.10.0-1160.42.2.el7/linux-3.10.0-1160.42.2.el7.x86_6/build

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#	make -C $(KDIR) SUBDIR=$(PWD) modules
#	make -C ${KDIR} M=$$PWD

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#	rm -rf *.o *.ko *.mod.* *.symvers *.order
	
