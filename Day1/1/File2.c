#include<linux/init.h>
#include<linux/module.h>

static void s_exit(void)
{
	printk(KERN_INFO "Exiting from the modules with two files...\n");
}

module_exit(s_exit);
