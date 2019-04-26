/*************************************************************************
    > File Name: mmamp2.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月17日 星期三 10时19分40秒
 ************************************************************************/

#include <iostream>
#include <bitset>
#include <algorithm>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
using namespace std;

string name("/tmp2");

const int loop=10;
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		cerr<<"to few arguements"<<endl;
		return 0;
	}
	//1.内核允许读写最后一页映射区以及远部分(内核的内存保护是以页为单位)
	//但是向着部分扩展区的任何文件内容都不会写到文件中
	//
	//2.如果内存映射大小大于文件大小，访问时出现SIGBUS错误，代表在内存映射
	//区访问时超出底层支持大小,也就是可以定义给mmap制定一个大于该对象大小的
	//参数，但是无法访问该对象以远的部分，即使对该对象的描述符也一样

	int mmapsize=atoi(argv[2]);
	int filesize=atoi(argv[1]);
	int fd=open("1.txt",O_CREAT|O_TRUNC|O_RDWR,FILE_MODE);
	if(fd<0)
	{
		cerr<<strerror(errno)<<endl;
		exit(fd);
	}
	//创建文件指定大小
	lseek(fd,filesize-1,SEEK_SET);
	write(fd,"",1);

	char *ptr=(char *)mmap(nullptr,mmapsize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	int pagesize=sysconf(_SC_PAGESIZE);
	cout<<"pagesize is: "<<pagesize<<endl;
	
	int i=0;
	int Max=max(filesize,mmapsize);
	for(i=0;i<Max;i+=pagesize)
	{
		cout<<"ptr["<<i<<"]="<<ptr[i]<<endl;
		ptr[i]=1;
		cout<<"ptr["<<i+pagesize-1<<"]="<<ptr[i+pagesize-1]<<endl;
		ptr[i+pagesize-1]=1;
	}
	//
	cout<<"ptr["<<i<<"]="<<ptr[i]<<endl;
	return 0;
}
