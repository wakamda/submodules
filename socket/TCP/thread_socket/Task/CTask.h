#ifndef CTASK_H
#define CTASK_H
#include <deque>
#include <string>  
#include <pthread.h>  
  
using namespace std;  
  
/** 
 * 执行任务的类，设置accept()描述符并执行 
 */  
class CTask {
protected:
    string m_strTaskName;   //任务的名称
    int connfd;    //接收的地址
 
public:
    CTask() = default;
    CTask(string &taskName): m_strTaskName(taskName), connfd(NULL) {}
    virtual int Run() = 0;
    void SetConnFd(int data);   //设置接收的套接字连接号。
    int GetConnFd();
    virtual ~CTask() {}
    
};


#endif //CTASK_H