#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>//linux下特有的头文件，主要包含了read，write等函数
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAXLINE 1024
#define PORT 7000

//server的动作：创建socket，绑定端口地址(先设置端口地址)，监听，开始接受accept，然后接收数据，关闭

int main()
{
    //buff
    char recvbuff[MAXLINE];
    char reply[MAXLINE] = "reply";
    int sock;
    int conn;

    //create
    if((sock=socket(AF_INET,SOCK_STREAM,0)) < 0){
        std::perror("Create socket failed!\n");
        exit(1);
    }

    //bind
    struct sockaddr_in  sockAddr;
    memset(&sockAddr,0,sizeof(sockAddr));// 各位清零
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_addr.s_addr=INADDR_ANY;
    sockAddr.sin_port=htons(PORT);
    if((bind(sock,(struct sockaddr*)&sockAddr,sizeof(sockAddr)) < 0)){
        std::perror("bind failed!\n");
        exit(1);
    }

    //listen
    if((listen(sock,10)) < 0){
        std::perror("listen failed!\n");
        exit(1);
    }

    printf("======listening......======\n");

    //accept
    conn=accept(sock,(struct sockaddr*)NULL,NULL);
    if(conn < 0)
    {
        std::perror("accept failed!\n");
        exit(1);
    }
    printf("======accepted!!!!Ready to receive...======\n");

#if 1
    //receive
    sleep(1);
    int n=recv(sock,recvbuff,MAXLINE,0);
    recvbuff[n] = '\0';
    std::cout << "receive:" << recvbuff << std::endl;
    printf("receive:%x\n",recvbuff);

    //reply
    //send(sock,reply,MAXLINE,0);
#endif

    close(conn);
    close(sock);
}