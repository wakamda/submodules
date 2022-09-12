#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>//linux下特有的头文件，主要包含了read，write等函数
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>

//#define BUFFER_SIZE 1024
#define MAXLINE 1024
#define PORT 7000

//client的动作：创建，设置端口地址，连接/注册

int main()
{
    
    int sock;
    int conn;
    char sendbuf[MAXLINE]="cli";
    char recvbuf[MAXLINE];

    //create
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock <0 )
    {
        printf("Create client_Socket Failed!\n");
        exit(1);
    }
    //set
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));//各位清零
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_addr.s_addr=inet_addr("10.20.45.136");  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）
    sockAddr.sin_port=htons(PORT);
    if(conn=connect(sock,(struct sockaddr*)&sockAddr,sizeof(sockAddr))<0)
    {
        perror("connect");
        exit(1);
    }

#if 1
    std::cout << "connected success" << std::endl;
    std::cout << "will send:" << sendbuf << std::endl;
    sleep(1);
    int n;
    if(n=send(sock,sendbuf,MAXLINE,0) < 0)
    {
        perror("send");
        exit(1);
    }

#endif

#if 0
    std::cout << "connected success" << std::endl; 
    while(1)
    {
        sleep(1);
        int n;
        if(n=send(sock,sendbuf,sizeof(sendbuf),0)<0)
        {
            perror("send");
            exit(1);
        }
        printf("send msg:%s\n",&sendbuf);
        //int r= recv(sock,recvbuf,sizeof(recvbuf),0);
        //if(r < 0){
        //    perror("recv");
        //    exit(1);
        //}
        //printf("recv msg:%s\n",&recvbuf);
    }
#endif

    close(sock);
    return 0;

}