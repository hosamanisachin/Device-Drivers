# Device-Drivers

 Device driver is a set of functions using them you can read / write from your hardware devices. Application calls the driver’s functions, and the driver functions performs operations on the device and gives results back to the application. So, the driver should have interface to talk to the application and the device both.  The application resides in the user space, driver resides in kernel space, and hardware is the physical layer.
So, a driver has two major functionalities.
1.    Interface with the application:
Driver should have functions using which application can place the request to a driver and the driver can send response back to application. Always it’s an application that sends some request to the driver. So, applications should have some interface for the drivers to initiate. 
2.    Interface with the device:
After receving the request from the application, the driver should know how to act upon the device to serve this request. For that the driver should be able to reach to the device. Driver code gets executed in CPU. CPU is connected to different devices using various bus technologies, e.g. PCI, serial ,USB etc. It means if your code wants to access the device, the code has to  access it through the bus. So, driver has functionality of accessing a hardware which is always bus specific. If device is using PCI bus,then this code will be PCI bus dependent. If the device is using USB bus ,then your code will be USB bus dependent etc.

![alt text](http://1.bp.blogspot.com/-YVK8uqeJt_M/VH5166t41bI/AAAAAAAAAHc/mDTJ3_8KgkA/s1600/Driver_Block.bmp.jpg)

So , above described two sets of functions together is a driver. So, a driver is a combination of the application specific function ( OS specific ) and the hardware specific functions ( bus specific ).


Linux device driver categories are broadly divided into three.

    Character Device Drivers
    Block / Storage Device Drivers
    Network Device Drivers

Character Device Drivers :

As the name suggests, character device drivers work upon character devices or the devices that read / write character by character. Character drivers operations are blocking operations. Blocking operations are also called the synchronous operations. For example, assume a scenario where an application wants to read from a character device. Application will call read() from user space. By the way same file system interface or file system calls are used for the device also, i.e. – read() / write() / lseek() etc..  The read() call from user space will invoke that particular device driver’s read call and the driver startsreading the device. As long as the driver is reading the device, the application has to wait for driver’s read to complete. Here the driver is said to beblocking on read call. Same is true for other calls also. This behaviour is called synchronous or blocking nature of character drivers. So, character device driver’s calls are blocking / synchronous in nature.

Block Device Drivers:

Block device drivers are those drivers that read or write on the device in blocks. They don’t read / write to the device character by character. Since these operations are in blocks, they are cpu intensive. These operations may take long time to finish. So, block drivers cant afford to be synchronous or blocking. They cant block on a single call to make user to wait for long time or in some cases endlessly. As a result, these drivers are made to be non-blocking or asynchronous in nature. That means , application submits the read / write request to the driver and will resume its work, whatever it was doing before. When the request gets completed, application will be notified, it doesn’t have to wait till the completion of the request. So, calls to the block device driversare non-blocking or asynchronous in nature.

Network Device Drivers:

As we saw, the character drivers are for the character devices and block drivers are for block devices. Similaraly network drivers are for networkcommunication devices. Example of network drivers include, usb network drivers, ethernet drivers , token ring drivers, atm drivers, wi-fi drivers, bluetooth network drivers etc.
The network drivers can be used only through L2-L3  protocol stacks. You can not directly use network drivers from application without using the unerlaying network subsystem.
