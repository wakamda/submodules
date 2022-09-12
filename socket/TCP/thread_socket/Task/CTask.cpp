#include "CTask.h"

void CTask::SetConnFd(int data)  
{  
    connfd = data;  
}  
 
int CTask::GetConnFd()
{
    return connfd;
}