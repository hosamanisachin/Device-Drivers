#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("BSD/GPL");
MODULE_AUTHOR("SACHIN HOSAMANI");
MODULE_DESCRIPTION("Module using Macro");

static int __init s_init(void)
{
	printk(KERN_INFO "This is module with macro");
	return(0);

}

static void __exit s_exit(void)
{
	printk(KERN_INFO "Exiting from module with macro");

}

module_init(s_init);
module_exit(s_exit);
