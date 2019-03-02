1) Create a file with name "ModuleParam.c"
//Module parameter are used to give config options while loading the module. And sometimes
//at runtime via sys/module entry
//The module parameter are static global variables and declard with module_param() macro.
// syntax module_param(var,datatype,permission)
// datatyep can be:
			a) bool
			b) invbool
			c) charp
			d) int
			e) short
			f) long
			g) uint
			h) ushort
			i) ulong
// syntax module_param_named(username,var,datatype,permission)
// syntax module_param_array(var,datatype,elements,permission)


NOTE: Module parameter value can be accessed using cat /sys/module/mod_name/parameters/param_name
	Can be modified while module is running echo value > /sys/module/mod_name/parameters/param_name
2) Create "Makefile" and type
	obj-m:=ModuleParam.o

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
if we need to pass the parameter 
	insmod ModuleParam.ko toWhom="Linux" howManyTimes=3

7) To check
	lsmod | head
=========================================================
output

Module                  Size  Used by
ModuleParam            12665  0 
tcp_lp                 12663  0 
rfcomm                 69552  2 
fuse                   91880  3 
xt_CHECKSUM            12549  1 
ipt_MASQUERADE         12678  3 
nf_nat_masquerade_ipv4    13412  1 ipt_MASQUERADE
tun                    31665  1 
devlink                42368  0 

  

8) To remove 
	rmmod simplemodule.ko

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
output with parameter 

[ 3540.603502] Hello Linux!!
[ 3540.603508] Hello Linux!!
[ 3540.603510] Hello Linux!!
[ 3567.577565] GOODBYE Linux!!
[ 3567.577571] GOODBYE Linux!!
[ 3567.577574] GOODBYE Linux!!



11) Exit super user
	exit

12) Clean all the files in the directory(step 4)
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
  
  
  
 
