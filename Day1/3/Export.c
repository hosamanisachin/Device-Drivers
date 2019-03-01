#include<linux/init.h>
#include<linux/module.h>
#include "importexport.h"

int num;

static int __init s_init(void)
{
	num=100;
	printk(KERN_INFO "This is module with export symbols \n");
	return(0);
}

static void __exit s_exit(void)
{
	printk(KERN_INFO "Exiting from export symbols module\n");
}

void exportedfunction(void)
{
	printk(KERN_INFO "I am exported function \n");
}


EXPORT_SYMBOL(exportedfunction);
EXPORT_SYMBOL(num);

module_init(s_init);
module_exit(s_exit);

MODULE_LICENSE("BSD/GPL");
MODULE_AUTHOR("SACHIN HOSAMANI");
MODULE_DESCRIPTION("Import Export");


