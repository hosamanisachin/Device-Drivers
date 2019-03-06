#include<linux/version.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/sched.h>

//global variable declaration
static dev_t first; //device number (major+minor)
static struct cdev my_char_dev; //char device struct
static struct class *my_device_class_ptr; //char device class pointer
#define MAXLEN 4000 //corresponds to 4k memory page size
static char mybuffer[MAXLEN];

//global function declarations
static int s_open(struct inode *inode_ptr, struct file *file_ptr)
{
	printk(KERN_INFO "SJH Driver's open(): PID of process using this device is %d\n",current->pid);
	return(0);
}

static int s_close(struct inode *inode_ptr, struct file *file_ptr)
{
	printk(KERN_INFO "SJH Drive's close()\n");
	return(0);
}

static ssize_t s_read(struct file *file_ptr, char __user *buffer, size_t length, loff_t *offset)
{//Read device adn transfer data from device to user space

	//variable dec
	int max_bytes;
	int bytes_to_read;
	int nbytes;

	max_bytes=MAXLEN-*offset; //how many bytes of data left in the buffer
	if(max_bytes>length)
		bytes_to_read=length;
	else
		bytes_to_read=max_bytes;
	if(bytes_to_read==0) //no data remaining 
	{
		printk(KERN_INFO "SJH Driver's read(): EOD(End Of Device)\n");
		return(-ENOSPC); // End or NO SPaCe Remainig
	}
	nbytes=bytes_to_read - copy_to_user(buffer,mybuffer+ *offset,bytes_to_read); //copy_to_user returns number of bytes not copied
	*offset=*offset+nbytes;
	return(nbytes);
}

static ssize_t s_write(struct file *file_ptr, const char __user *buffer, size_t length, loff_t *offset)
{//write the device and transfers data from user-space to device

	//variable dec
	int max_bytes;
	int bytes_to_write;
	int nbytes;

	max_bytes=MAXLEN-*offset;
	if(max_bytes>length)
		bytes_to_write=length;
	else
		bytes_to_write=max_bytes;
	if(bytes_to_write==0)
	{
		printk(KERN_INFO "SJH Driver's write() : EOD(End Of Device)\n");
		return(-ENOSPC); // End or NO SPaCe Remainig
	}
	nbytes=bytes_to_write - copy_from_user(mybuffer+*offset,buffer,bytes_to_write); //copy_from_user returns number of bytes not copied
	*offset = *offset+nbytes;
	return(nbytes);
}


static loff_t s_lseek(struct file *file_ptr, loff_t offset, int origin)
{
	//variable dec
	loff_t new_pos=0;

	switch(origin)
	{
		case 0:
			new_pos=offset;
			break;
		case 1:
			new_pos=file_ptr->f_pos+offset; //f_pos gives the current position
			break;
		case 2:
			new_pos=MAXLEN-offset;
			break;
	}

	if(new_pos>MAXLEN)
		new_pos=MAXLEN;
	if(new_pos<0)
		new_pos=0;
	file_ptr->f_pos=new_pos;
	return(new_pos);
}
//initialise struct cdev
static struct file_operations s_fops = { .owner=THIS_MODULE,
										.open=s_open,
										.release=s_close,
										.read=s_read,
										.write=s_write,
										.llseek=s_lseek
};

static int __init s_init(void)
{
	int major=250; //hardcoded 250
	int minor=0;
//allocate major and minor number to our device
	first=MKDEV(major,minor);


//alloc_chrdev_region(&devno,baseminor,count,devname);
	if(alloc_chrdev_region(&first,0,1,"SJH")<0) // can check in /proc/devices
		return(-1);

		//create device class and device file class_create(module,class_name); retunr pointer
	if((my_device_class_ptr=class_create(THIS_MODULE,"sjh_chardev_class"))==NULL) // /sys/classes/
	{
		unregister_chrdev_region(first,1);
		return(-1);
	}
	// create device in /dev and entry under /sys/devices/virtual it gives following infor
	// a) dev -> to display major/minor number
	// b) power -> power consumed by the device (ACPI)
	// c) subsystem -> vendorID/ deviceID
	// d) uevent -> events related to hotplug of HID devices
	if(device_create(my_device_class_ptr,NULL,first,NULL,"sjh_chardev")==NULL) // /dev/
	{
		class_destroy(my_device_class_ptr);
		unregister_chrdev_region(first,1);
		return(-1);
	}

	cdev_init(&my_char_dev,&s_fops);
	if(cdev_add(&my_char_dev,first,1)==-1)
	{
		device_destroy(my_device_class_ptr,first);
		class_destroy(my_device_class_ptr);
		unregister_chrdev_region(first,1);
		return(-1);
	}
	
	printk(KERN_INFO "Welcome by SJH: Linux Character Device Driver is Successfully Registered. \n");
	return(0);
}

static void __exit s_exit(void)
{
	cdev_del(&my_char_dev); //delete from kernel database 
	device_destroy(my_device_class_ptr,first); // destroy from /dev and /sys/devices/virtual
	class_destroy(my_device_class_ptr); //destroy from /sys/class
	unregister_chrdev_region(first,1); //release device number allocated to the device
	printk(KERN_INFO "GOODBYE by SJH: Linux Character Device Driver is Successfully Unregistered. \n");
}

module_init(s_init);
module_exit(s_exit);

MODULE_LICENSE("GPL"); //USE ONLY GPL or might encouter error to use only GPL symbol
MODULE_AUTHOR("SACHIN HOSAMANI");
MODULE_DESCRIPTION("SJH: CHARACTER DEVICE DRIVER");
