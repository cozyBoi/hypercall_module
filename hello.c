#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/init.h>
#include<linux/linkage.h>
 #include<uapi/linux/kvm_para.h>
 #include<linux/cpumask.h>
//#include <sys/mman.h> //mlock to prevent swap out
//#include <sys/types.h>
//#include <sys/errno.h>
//#include <sys/pin.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshmanan");
MODULE_DESCRIPTION("A Simple Hello World module");

unsigned char dump_space[16];

long long int pow16(int p){
    int i = 0;
    long long int ret = 1;
    for(i = 0; i < p; i++){
        ret *= 16;
    }
    return ret;
}

static int __init hello_init(void)
{
    int i = 0;
    long int high_addr = 0, low_addr = 0;
    long long int addr = 0;
    char address_char[30];
	printk(KERN_INFO "Hello world!\n");
    //mlock(dump_space, 16);
    for(i = 0; i < 16; i++){
        dump_space[i] = 0x00;
    }
	printk(KERN_INFO "Hypercall %p\n", dump_space);
    
    addr = (long long int)dump_space;
    
    high_addr = (long int)(addr / pow16(8) / pow16(8));
    low_addr = (long int)(addr % pow16(8));
    
    printk("high %lx low %lx\n", high_addr, low_addr);
    
	kvm_hypercall2(12, high_addr, low_addr);
	return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
    //munlock(dump_space, 16);
    printk(KERN_INFO "Cleaning up module.\n");
}
 
module_init(hello_init);


