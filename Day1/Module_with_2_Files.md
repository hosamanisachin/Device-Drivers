1) Create two files, write module's code in both of them and name them as "File1.c" and "File2.c"

2) Create "Makefile" and type
	obj-m:=simplemodule.o
	simplemodule-objs:= File1.c File2.c

//The second line '-objs' is prepended to the module name give in 1st line i.e after 'obj-m:=' but now without any extension.

3) To build our module/driver(simplemodule.ko) execute the following
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
  
  *-C means change to directory.
  * M= means to build all needed files and link final module images.

4)Following files will be created 
	a) .mod.c - vermagic number
	b) .ko  - actual driver by linking .mod.o and .o
	c) .symvers  - contains external symbols defined by us and hence not [resent in kernel's symvers
	d) .o - object code
	e) .order - list the order of compilation and creation of .ko occurs
	f) .mod.o - object code created from mod.c

5) su

6) To insert the moduel 
	insmod simplemodule.ko

7) To check
	lsmod | head
 =========================================================
output

Module                  Size  Used by
simplemodule           12488  0 
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4 13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 
ip6t_rpfilter          12595  1 
  

8) To remove 
	rmmod simplemodule.ko

9) Repeat step 7.
  lsmod | head
   =========================================================
output

Module                  Size  Used by
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4 13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 
ip6t_rpfilter          12595  1 
ipt_REJECT             12541  4 

10) To check kernel logs
	dmesg | tail
  =========================================================
output

[   41.614444] ---[ end trace 012059875da013d1 ]---
[   41.614502] sched: RT throttling activated
[   42.732677] Bluetooth: RFCOMM TTY layer initialized
[   42.732686] Bluetooth: RFCOMM socket layer initialized
[   42.732812] Bluetooth: RFCOMM ver 1.11
[   44.681611] rfkill: input handler disabled
[  470.659452] simple: module license 'DUAL BSD/GPL' taints kernel.
[  470.659457] Disabling lock debugging due to kernel taint
[  470.659805] This is the module with two files...
[  480.107144] Exiting from the modules with two files...


11) Exit super user
	exit

12) Clean all the files in the directory(step 4)
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
  
  
  
 
