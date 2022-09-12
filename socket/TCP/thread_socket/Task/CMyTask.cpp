#include "CMyTask.h"

int CMyTask::Run()
    {
        
        int connfd= GetConnFd();
        while(1)
        {
            char recvbuf[1024];
            char sendbuf[1024];
          
            memset(recvbuf,0x00,sizeof(recvbuf));
            memset(sendbuf,0x00,sizeof(sendbuf));
            
            int len = recv(connfd,recvbuf,sizeof(recvbuf),0);
            if(len <= 0)
                printf("no buf.\n");
            printf("%s \n",recvbuf);
            printf("Please input: ");
            fflush(stdout);
            fgets(sendbuf,1024,stdin);
            if(strncmp(sendbuf,"end",3)==0)  
            {  
                close(connfd);  
                break;  
            }  
            send(connfd,sendbuf,sizeof(sendbuf),0);
                    
        }
        close(connfd);
        return 0;
    }