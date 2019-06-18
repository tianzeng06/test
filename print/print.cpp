#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

typedef struct Fd
{
	int fd1;
	int fd2;
}Fd;
Fd f;

//有无I/O缓冲的函数能否一起使用
void *readFileFromWellToPrint(void *arg)
{
	Fd fd=*(Fd *)arg;
	int fd1=fd.fd1;
	int fd2=fd.fd2;

	while(true)
	{
		struct flock lock;
		lock.l_type=F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=0;
		lock.l_len=0;
		int res=fcntl(fd1,F_SETLK,&lock);
		if(res<0)
		{
			cerr<<"thread lock wellFile.txt error: "<<strerror(errno)<<endl;
			continue;
		}
		/*
		 * read(fd,path,20)文件指针不移动
		 * */
		
		char path[20];
		memset(path,'\0',20);
		char c;
		int i=0;
		while((res=read(fd1,&c,1))>0)
		{
			if(c=='\n'||c==EOF)
				break;
			path[i++]=c;
		}
		path[i]='\0';
		if(path[0]!='\0')
		{
			cout<<path<<": "<<strlen(path)<<endl;
			int fd3=open(path,O_RDWR);
			if(fd3<0)
			{
				cerr<<strerror(errno)<<endl;
				exit(errno);
			}

			int n=0;
			char str[4096];
			memset(str,'\0',4096);
			while((n=read(fd3,str,4096))>0)
				write(fd2,str,strlen(str));
			if(c==EOF)
				write(fd2,"\n",1);
		}

		lock.l_type=F_UNLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=0;
		lock.l_len=0;
		res=fcntl(fd1,F_SETLK,&lock);
		if(res<0)
		{
			cerr<<"thread unlock wellFile.txt error: "<<strerror(errno)<<endl;
			exit(errno);
		}
	}
	return nullptr;
}

int main()
{
	int fd=open("./wellFile.txt",O_CREAT|O_TRUNC|O_RDWR,0664);
    if(fd<0)
    {
		cerr<<strerror(errno)<<endl;
		exit(errno);
	}

    int fd1=open("./out.txt",O_CREAT|O_TRUNC|O_RDWR,0664);
    if(fd1<0)
    {
        cerr<<strerror(errno)<<endl;
        exit(errno);
	}

	f.fd1=fd;
	f.fd2=fd1;

	pthread_t tid;
	if(pthread_create(&tid,nullptr,readFileFromWellToPrint,&f)==-1)
	{
		cerr<<"create printer thread error: "<<strerror(errno)<<endl;
		exit(0);
	}

	int stauts=-1;
	string path;
	while(true)
	{
		cin>>path;
		if(path.empty()||path.at(0)!='/')
		{
			cerr<<"input file name error"<<endl;
			continue;
		}

		pid_t pid=fork();
		if(pid<0)
		{
			cerr<<"fork error: "<<strerror(errno)<<endl;
			exit(errno);
		}
		else if(pid==0)
		{
			close(fd);
			close(fd1);
				
			int fd2=open("./wellFile.txt",O_RDWR|O_APPEND);//写成固定文件,可用pipe传输
		    if(fd<0)
		    {
				cerr<<strerror(errno)<<endl;
				exit(errno);
			}

		AGAIN:
			struct flock lock;
			lock.l_type=F_WRLCK;
			lock.l_whence=SEEK_SET;
			lock.l_start=0;
			lock.l_len=0;
			int res=fcntl(fd2,F_SETLK,&lock);
			if(res<0)
			{
				cerr<<"child lock wellFile.txt error: "<<strerror(errno)<<endl;
				goto AGAIN;
			}

			write(fd2,path.c_str(),path.length());
			write(fd2,"\n",1);

			lock.l_type=F_UNLCK;
			lock.l_whence=SEEK_SET;
			lock.l_start=0;
			lock.l_len=0;
			res=fcntl(fd2,F_SETLK,&lock);
			if(res<0)
			{
				cerr<<"child unlock wellFil.txte errno: "<<strerror(errno)<<endl;
				exit(errno);
			}
			exit(0);
		}
		else if(pid>0)
			wait(&stauts);
	}
	return 0;
}
