#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/linkage.h>
#include <uapi/linux/kvm_para.h>
#include <linux/cpumask.h>
#include <linux/delay.h>
//#include <linux/mm_type.h>
//#include <sys/mman.h> //mlock to prevent swap out
//#include <sys/types.h>
//#include <sys/errno.h>
//#include <sys/pin.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshmanan");
MODULE_DESCRIPTION("A Simple Hello World module");

unsigned long long int dump_space = 1;

extern struct mem_section *mem_section[NR_SECTION_ROOTS];
extern inline struct mem_section *__pfn_to_section(unsigned long pfn);
extern unsigned long usr_page_to_pfn(struct page *page);
extern struct page* usr_pfn_to_page(unsigned long pfn);

unsigned long long int pow16(int p){
    int i = 0;
    unsigned long long int ret = 1;
    for(i = 0; i < p; i++){
        ret *= 16;
    }
    return ret;
}

static int __init hello_init(void)
{
    int i = 0;
    long int high_addr = 0, low_addr = 0;
    unsigned long long int addr = 0;
	struct page*curr_page = NULL;
	unsigned long int curr_pfn;
	/*
    for(i = 0; i < 16; i++){
        dump_space[i] = 0x00;
    }
    for(i = 0; i < 16; i++){
        printk("%x ", dump_space[i]);
    }
	printk("\n");
	printk(KERN_INFO "Hypercall %p\n", dump_space);
	*/
	printk(KERN_INFO "Hypercall\n");
	printk("dump data %llx\n", dump_space);
    
    addr = (unsigned long long int)&dump_space;
	
    high_addr = (long int)(addr / pow16(8));
    low_addr = (long int)(addr % pow16(8));
    
    printk("high %lx low %lx\n", high_addr, low_addr);
    
	kvm_hypercall2(12, high_addr, low_addr);

	usleep_range(1000000, 1000001);
	/*
    for(i = 0; i < 16; i++){
        printk("%x ", dump_space[i]);
    }
	printk("\n");
	*/
	printk("dump data %llx\n", dump_space);
	curr_pfn = dump_space >> 12;
	curr_page = usr_pfn_to_page(curr_pfn);
	printk("page_to_pfn %lx\n", usr_page_to_pfn(curr_page));
	printk("mapping %p\n", curr_page->mapping);
	/*
	struct mem_section *curr_memsect = __pfn_to_section(curr_pfn);
	printk("mem_section %p\n", curr_memsect);
	printk("before curr_pages %p\n", curr_pages);
	curr_pages = curr_memsect->section_mem_map;
	printk("after curr_pages %p\n", curr_pages);
	for(i = 0; i < 256 * 1024; i++){
		void*tmp = page_to_phys(&curr_pages[i]);
		if(tmp == (void*)dump_space){
			printk("page_to_phys %p\n", tmp);
		}
	}*/
	return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
    //munlock(dump_space, 16);
    printk(KERN_INFO "Cleaning up module.\n");
}
 
module_init(hello_init);


