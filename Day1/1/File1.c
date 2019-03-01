#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("DUAL BSD/GPL");
MODULE_AUTHOR("SACHIN_HOSAMANI");
MODULE_DESCRIPTION("SJH: Two Kernel Module");

static int s_init(void)
{
	printk(KERN_INFO "This is the module with two files...\n");
	return(0);
}

module_init(s_init);
