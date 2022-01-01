#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/init.h>
#include<linux/linkage.h>
 #include<uapi/linux/kvm_para.h>
 #include<linux/cpumask.h>
#include <sys/mman.h> //mlock to prevent swap out
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshmanan");
MODULE_DESCRIPTION("A Simple Hello World module");

unsigned char dump_space[16];

static int __init hello_init(void)
{
    int i = 0;
	printk(KERN_INFO "Hello world!\n");
    mlock(dump_space, 16);
    for(i = 0; i < 16; i++){
        dump_space[i] = 0x00 + i;
    }
	kvm_hypercall1(12, dump_space);
	return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
    munlock(dump_space, 16);
    printk(KERN_INFO "Cleaning up module.\n");
}
 
module_init(hello_init);


