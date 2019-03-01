1) Create files with name "Import.c" , "Export.c" and "importexport.h"

2) Create "Makefile" and type
	obj-m:=Import.o Export.o
//we will be inserting two modules

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

6) To insert the moduel //first we need to insert "Export" module since "Import" module will work only upon "Export" module has sent something
// #"Dusre bhasha mein" Import.ko depends on Export.ko	
	insmod Export.ko
	insmod Import.ko


7) To check
	lsmod | head
=========================================================
output

Module                  Size  Used by
Import                 12421  0 
Export                 12757  1 Import
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4    13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 
  

8) To remove  // remove the dependent module first i.e Import.ko
	rmmod Import.ko
	rmmod Export.ko

9) Repeat step 7.
  lsmod | head
=========================================================
output

Module                  Size  Used by
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4    13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 
ip6t_rpfilter          12595  1 
ipt_REJECT             12541  4 


10) To check kernel logs
	dmesg | tail
=========================================================
output

[ 7750.616629] Import: Unknown symbol num (err 0)
[ 7750.616682] Import: Unknown symbol exportedfunction (err 0)
[ 7803.025694] Export: Unknown symbol num (err 0)
[ 7998.678114] Export: Unknown symbol num (err 0)
[ 8339.801715] This is module with export symbols 
[ 8347.952203] This is module with import symbol 
[ 8347.952209] I am exported function 
[ 8347.952211] Imported symbol num=100 
[ 8427.596263] Exiting from import symbol module 
[ 8433.355555] Exiting from export symbols module

//There is error on using the importexport.h file

11) Exit super user
	exit

12) Clean all the files in the directory(step 4)
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
