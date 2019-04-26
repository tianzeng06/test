/*************************************************************************
    > File Name: file.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年02月28日 星期四 00时26分24秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <fcntl.h>
#include <cstring>
using namespace std;

int main()
{
	int fd=open("/home/ctz/work/1.txt",O_RDONLY);
	if(fd!=-1)
		cout<<"success"<<endl;
	else
		cerr<<strerror(errno)<<endl;

	int pipe1[2];
	pipe(pipe1);
	close(pipe1[0]);
	
	string buf;
	buf.resize(60);
	ssize_t n=0;
	while((n=read(fd,(void*)buf.c_str(),59))>0)
	{
		ssize_t t=write(pipe1[1],buf.c_str(),n);
		cout<<t<<endl;
		if(t<0)
			cerr<<strerror(errno)<<endl;
	}

	pid_t cpid;
	if((cpid=fork())==0)
	{
		string buf1;
		buf1.resize(60);
		ssize_t n1=0;
		while((n1=read(pipe1[0],(void*)buf1.c_str(),59))>0)
			write(STDOUT_FILENO,buf1.c_str(),n1);
	}
	close(pipe1[0]);
	close(pipe1[1]);
	close(fd);
	return 0;
}
