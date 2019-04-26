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
		void (*fun_ptr)(void *);
		void *arg;
	public:
		Task(void (*fun)(void *),void *a):fun_ptr(fun),arg(a){}
		void run(const pthread_t tid);

};
