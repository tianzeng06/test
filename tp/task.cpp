/*************************************************************************
    > File Name: task.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月29日 星期五 19时17分09秒
 ************************************************************************/

#include "task.h"

void Task::run(const pthread_t tid)
{
	cout<<"thread: "<<tid<<" working,";
	(*fun_ptr)(arg);
	//sleep(1);
	cout<<"thread: "<<tid<<" working end"<<endl;
}
