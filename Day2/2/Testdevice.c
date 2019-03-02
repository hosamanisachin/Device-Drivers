//To test our character device driver

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>

int main(void)
{
	int i,fd,retval;
	off_t offset;
	char buf[100]="My Name Is SACHIN JAGADISH HOSAMANI: SJH\0"; 
	//open device
	fd=open("/dev/sjh_chardev",O_RDWR); // read and write
	if(fd==-1)
	{
		printf("SJH Device Test: Device opening failed. Exiting\n");
		perror("SJHError:");
		printf("ERRNO: %d",errno);
		exit(1);
	}

	//write buffers contents into device as write() demo
	retval = write(fd,buf,sizeof(buf));
	if(retval==-1)
	{
		printf("SJH Device Test: Device writing error.Exiting\n");
		close(fd);
		perror("SJHError:");
		printf("ERRNO: %d\n",errno);
		exit(1);
	}

	//print buffer contents
	printf("After device writing operation, the device contents: \n %s\n",buf);

	//seek 16 characters ahead in device i.e skip first 16 chars 
	offset=lseek(fd,16,SEEK_SET);
	printf("File pointer is positioned at %d \n",offset);

	//read 32 characters from deice 16th position into the buffer
	retval=read(fd,buf,32);
	if(retval==-1)
	{
		printf("SJH Device Test: Device writing error.Exiting\n");
		close(fd);
		perror("SJHError:");
		printf("ERRNO: %d\n",errno);
		exit(1);
	}
	//print buffer contents
	printf("After deivce seeking and reading operations, the buffer contents : \n %s \n",buf);
	//close the deivce
	close(fd);
	return 0;
}
