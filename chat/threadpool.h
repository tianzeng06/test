/*************************************************************************
    > File Name: threadpool.h
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2018年11月22日 星期四 20时32分12秒
 ************************************************************************/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <vector>
#include <exception>
#include <errno.h>
#include "lock.h"
#define MAX_THREADS 1024

using namespace std;

template <class T>
class Threadpool
{
	private:
		int idle;//线程池中空闲线程的数量
		int num;//线程池中线程数
		//pthread_t *threads;//线程数组
		vector<pthread_t> idle_tid;//空闲线程的集合
		vector<pthread_t> busy_tid;//正在执行任务的线程的集合
		queue<T *> task_queue;//任务队列
		Mutex mutex;//互斥锁
		Cond cond;//条件变量锁
	    bool is_stop;//是否结束线程

	public:
		static void *worker(void *arg);//线程函数，里面执行run函数
		void run();
		T *get_task();//获取任务函数
		int mv_to_idle(pthread_t tid);//执行任务完成后，放入空闲
		int mv_to_busy(pthread_t tid);//移入到忙碌线程中

	public:
		Threadpool(int n=20);
		~Threadpool();
		bool append_task(T *task);//添加任务函数
		void start();//开始创建线程池
		void stop();//线程停止函数
};

template <class T>
Threadpool<T>::Threadpool(int n):num(n),idle(n),is_stop(false)
									   //,threads(NULL)
{
	if(num<=0)
	{
		cerr<<"threadpool can't init because num<=0."<<endl;
		exit(1);
	}
/*
	threads=new pthread_t[num];//创建线程数组
	if(threads==NULL)
	{
		cerr<<"can't init threadpool because thread carry can't new"<<endl;
		exit(1);
	}
	*/
}

template <class T>
Threadpool<T>::~Threadpool()
{
	//delete []threads;
	stop();
}

template <class T>
bool Threadpool<T>::append_task(T *task)
{
	mutex.mutex_lock();//临界资源上锁

	bool is_signal=task_queue.empty();
	task_queue.push(task);

	mutex.mutex_unlock();//解锁

	if(is_signal)//signal to null queue
		cond.signal();

	return true;
}

template <class T>
void Threadpool<T>::start()
{
	for(int i=0;i<num;++i)	
	{
		pthread_t tid;
		if(pthread_create(&tid,NULL,worker,this)!=0)
		{
			//delete []threads;
			throw exception();
			exit(1);
		}
		idle_tid.push_back(tid);//加入到空闲线程集合

		/*
		if(pthread_detach(threads[i])!=0)
		{
			delete []threads;
			throw exception();
			exit(1);
		}*/
	}
}

template <class T>
void Threadpool<T>::stop()
{
	is_stop=true;
	cond.broadcast();
}

template <class T>
void *Threadpool<T>::worker(void *arg)
{
	Threadpool<T> *thread=(Threadpool<T> *)arg;
	thread->run();//调用线程运行函数，真正执行工作的函数
	return thread;
}

template <class T>
void Threadpool<T>::run()
{
	pthread_t tid=pthread_self();
	//Threadpool<T> *thread=(Threadpool<T> *)arg;

	//mutex.mutex_lock();
	while(1)//if
	{
		T *task=get_task();
		if(task==NULL)
		{
			cerr<<"task_queue is null.wait()"<<endl;
			cond.wait();
		}
		else
		{
			mv_to_busy(tid);
			task->doit();//工作函数
			mv_to_idle(tid);
		}
	}
	//mutex.mutex_unlock();
}

template <class T>
T *Threadpool<T>::get_task()
{
	T *task=NULL;
	
	mutex.mutex_lock();
	if(!task_queue.empty())
	{
		task=task_queue.front();
		task_queue.pop();
	}
	mutex.mutex_unlock();

	return task;
}

template <class T>
int Threadpool<T>::mv_to_idle(pthread_t tid)
{
	vector<pthread_t>::iterator busy_iter=busy_tid.begin();
	while(busy_iter!=busy_tid.end())
	{
		if(tid==*busy_iter)
			break;
		++busy_iter;
	}	
	
	mutex.mutex_lock();
	busy_tid.erase(busy_iter);//此线程空闲，从繁忙任务队列中移除
	idle_tid.push_back(tid);//添加到空闲线程集合中

	//mutex.mutex_lock();
	++idle;
	mutex.mutex_unlock();
	return 0;
}

template <class T>
int Threadpool<T>::mv_to_busy(pthread_t tid)
{
	vector<pthread_t>::iterator idle_iter=idle_tid.begin();
	while(idle_iter!=idle_tid.end())
	{
		if(tid==*idle_iter)
			break;
		++idle_iter;
	}
	mutex.mutex_lock();
	idle_tid.erase(idle_iter);
	busy_tid.push_back(tid);

	//mutex.mutex_lock();
	--idle;
	mutex.mutex_unlock();
}

#endif
