#include<linux/init.h>
#include<linux/module.h>
#include "importexport.h"

extern int num;

static int __init s_init(void)
{
	printk(KERN_INFO "This is module with import symbol \n");
	exportedfunction();
	printk(KERN_INFO "Imported symbol num=%d \n",num);
	return(0);
}

static void __exit s_exit(void)
{
	printk(KERN_INFO "Exiting from import symbol module \n");
}

module_init(s_init);
module_exit(s_exit);

MODULE_LICENSE("BSD/GPL");
MODULE_AUTHOR("SACHIN HOSAMANI");
MODULE_DESCRIPTION("Import Export");
