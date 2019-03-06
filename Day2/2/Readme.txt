1) Create a file with name "CharDevDrv.c"


2) Create "Makefile" and type
	obj-m:=CharDevDrv.o

// obj-y --> static components of obj files
// obj-m --> dynamic components of obj files
// obj-n --> modules not linked with kernel(as per config)
	

3) To build our module/driver(simplemodule.ko) execute the following
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
  //basic command is "make modules"
  // -C /lib/modules/xxxx/build has a makefile so we invoke this Makefile to create our modules
	//* /build is symbolic link to the kernel source directory
  *-C means change to directory.
  * M= means to build all needed files and link final module images from current directory only.

4)Following files will be created 
	a) .mod.c - vermagic number
	b) .ko  - actual driver by linking .mod.o and .o
	c) .symvers  - contains external symbols defined by us and hence not [resent in kernel's symvers
	d) .o - object code
	e) .order - list the order of compilation and creation of .ko occurs
	f) .mod.o - object code created from mod.c

5) su

6) To insert the moduel 
	insmod ModuleParam.ko


7) To check
	lsmod | head
=========================================================
output

Module                  Size  Used by
CharDevDrv             12567  0 
tcp_lp                 12663  0 
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4    13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 

  
7.1) Check whether our device's device class directory is created (mentioned in quotes)
	ls /sys/class

[acer@acer 5]$ ls /sys/class | grep s
bsg graphicsc iscsi_connection iscsi_endpoint iscsi_host iscsi_iface iscsi_session iscsi_transport
leds mdio_bus memstick_host misc mmc_host msr pci_bus pcmcia_socket power_supply scsi_device
scsi_disk scsi_generic scsi_host "sjh_chardev_class" sound spi_master usbmon vtconsole 

7.2) Check that inside our device class directory, whether our device is listed
	ls -l /sys/class/sjh_chardev_class
=========================================================
output


total 0
lrwxrwxrwx. 1 root root 0 Mar  2 19:35 sjh_chrdev -> ../../devices/virtual/sjh_chardev_class/sjh_chardev

7.3) Go inside our device's directory
	ls -l /sys/class/sjh_chardev_class/sjh_chardev/

=========================================================
output


total 0
-r--r--r--. 1 root root 4096 Mar  2 19:37 dev
drwxr-xr-x. 2 root root    0 Mar  2 19:37 power
lrwxrwxrwx. 1 root root    0 Mar  2 19:37 subsystem -> ../../../../class/sjh_chardev_class
-rw-r--r--. 1 root root 4096 Mar  2 19:28 uevent

7.4) Read device directory "dev" file
	cat /sys/class/sjh_chardev_class/sjh_chardev/dev
=========================================================
output

243:0 //major and minor number dynamically we got 243 instead of 250

7.4.1)To cross check our deivce major and minor number 
	ls -l /dev/sjh_chardev
=========================================================
output

crw-------. 1 root root 243, 0 Mar  2 19:28 /dev/sjh_chardev

//first letter c denotes character device

7.5) To see whether our device name we gave in alloc_chrdev_region() function i.e SJH is 
	present in /proc/devices and also to see whether this named device has got major number 
	
	cat /proc/devices | grep "SJH"

=========================================================
output

243 SJH

9) Write a .c file to test our device driver functions and later check kernel log to find out what our device was doing
=========================================================
output

After device writing operation, the device contents: 
 My Name Is SACHIN JAGADISH HOSAMANI: SJH
File pointer is positioned at 16 
After deivce seeking and reading operations, the buffer contents : 
 N JAGADISH HOSAMANI: SJH 


8) To remove 
	rmmod CharDevDrv.ko

8.1) Repeat step 7.5 to check if unregistered.
9) Repeat step 7.
  lsmod | head
=========================================================
output

Module                  Size  Used by
tcp_lp                 12663  0 
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4    13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 
ip6t_rpfilter          12595  1 


10) To check kernel logs
	dmesg | tail
=========================================================
output

[17254.923750] Welcome by SJH: Linux Character Device Driver is Successfully Registered. 
[18734.843677] GOODBYE by SJH: Linux Character Device Driver is Successfully Unregistered. 



11) Exit super user
	exit

12) Clean all the files in the directory(step 4)
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
  
  
  
 
