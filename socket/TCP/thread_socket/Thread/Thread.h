#ifndef __THREAD_H  
#define __THREAD_H  
 
/*********************
** Filename: Thread.h
** Dsricbe: 线程池头文件
***/
 
 
#include <deque>
#include <string>  
#include <pthread.h>  
#include "../Task/CTask.h"
 
/** 
 * 线程池类的实现 
 */  
class CThreadPool  
{  
private:  
    static  deque<CTask*> m_deqTaskList;     /** 任务队列 */  
    static  bool shutdown;                    /** 线程退出标志 */           
    int     m_iThreadNum;                     /** 线程池中启动的线程数 */  
    pthread_t   *pthread_id;  
      
    static pthread_mutex_t m_pthreadMutex;    /** 线程同步锁 */  
    static pthread_cond_t m_pthreadCond;      /** 线程同步的条件变量 */  
  
protected:  
    static void* ThreadFunc(void * threadData); /** 新线程的线程回调函数 */  
    static int MoveToIdle(pthread_t tid);       /** 线程执行结束后，把自己放入到空闲线程中 */  
    static int MoveToBusy(pthread_t tid);       /** 移入到忙碌线程中去 */  
      
    int Create();          /** 创建线程池中的线程 */  
  
public:  
    CThreadPool(int threadNum = 10);  
    int AddTask(CTask *task);      /** 把任务添加到任务队列中 */  
    int StopAll();                 /** 使线程池中的线程退出 */  
    int getTaskSize();             /** 获取当前任务队列中的任务数 */  
};  
  
#endif  