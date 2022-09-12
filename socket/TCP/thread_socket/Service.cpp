/**********************
** FileName: Service.cpp
** Dscribe: 服务端程序
***/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "Thread.h"
#include "Task/CMyTask.h"

int main(int argc, char* argv[])
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd!=-1);
    struct sockaddr_in ser,cli;
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    inet_aton("127.0.0.1",&ser.sin_addr);
    ser.sin_port=htons(6500);
 
    int res=bind(sockfd,(struct sockaddr*)&ser,sizeof(ser));
    assert(res!=-1);
 
    listen(sockfd,5);
    
    //创建线程池
    CThreadPool Pool(5);

    
    while(1)
    {
       socklen_t len=sizeof(cli);
       int connectfd=accept(sockfd,(struct sockaddr*)&cli,&len);
       if(connectfd<0)
       {
           printf("cli connect failed.");

       
       }
       //收到客户端请求，即添加到任务队列去
       else
       {
           CTask* ta=new CMyTask;
           ta->SetConnFd(connectfd);
           Pool.AddTask(ta);
       }
      
      
      
    }
    close(sockfd);
    return 0;
 
    
}
 
 
 