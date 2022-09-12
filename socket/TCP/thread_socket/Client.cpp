#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
 
int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    // assert(sockfd!=-1);
   
     struct sockaddr_in ser,cli;
     memset(&ser,0x00,sizeof(ser));
     ser.sin_family=AF_INET;
     inet_aton("127.0.0.1",&ser.sin_addr);
     ser.sin_port=htons(6500);
 
 
    int res=connect(sockfd,(struct sockaddr*)&ser,sizeof(ser));  
   //assert(res!=-1); 
 
    while(1)
   {
        printf("please input:");  
        fflush(stdout);  
        char buff[128]={0};  
        fgets(buff,128,stdin);
        //std::cin>>buff;
        if(strncmp(buff,"end",3)==0)  
        {  
            close(sockfd);  
            break;  
        }  
        send(sockfd,buff,strlen(buff)-1,0);  
        memset(buff,0,128);  
        recv(sockfd,buff,127,0);  
        printf("%s\n",buff); 
       
   }
   close(sockfd);
   return 0;
 
}