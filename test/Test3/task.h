/*************************************************************************
    > File Name: task.h
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月29日 星期五 19时04分20秒
 ************************************************************************/

#pragma once
#include "head.h"

class Task
{
	private:
		char buff[1024];
		int fd;
	public:
		Task(char *s,int f):fd(f)
		{
			memset(buff,'\0',1024);
			strcpy(buff,s);
		}
		void run(const pthread_t tid);

};
