#include<linux/init.h>
#include<linux/module.h>

static char *toWhom="World";
static int howManyTimes=1;

module_param(toWhom,charp,S_IRUGO);
module_param(howManyTimes,int,S_IRUGO);
static int __init s_init(void)
{
	int i;
	for(i=0;i<howManyTimes;i++)
		printk(KERN_INFO "Hello %s!!\n",toWhom);
	return(0);
}

static void __exit s_exit(void)
{
	int i;
	for(i=0;i<howManyTimes;i++)
		printk(KERN_INFO "GOODBYE %s!!\n",toWhom);

}

module_init(s_init);
module_exit(s_exit);

MODULE_LICENSE("BSD/GPL");
MODULE_AUTHOR("SACHIN HOSAMANI");
MODULE_DESCRIPTION("MODULE PARAM");
MODULE_VERSION("1.0");
