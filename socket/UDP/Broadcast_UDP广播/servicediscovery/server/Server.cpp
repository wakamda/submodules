#include "Server.h"
#include "../clog/Log.h"

#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>  
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define LOG_TAG "server"

SendClass::SendClass(){

}
SendClass::~SendClass(){

}

//创建udp 广播 send socket
int SendClass::createUdpSocket(){

    //struct sockaddr_in udpClient_addr;
    //udpClient_addr.sin_family = AF_INET;
    //udpClient_addr.sin_port = htons(this->udpAndTcpPort);
    //inet_pton(AF_INET, this->udpBoardcastAddr, &udpClient_addr.sin_addr.s_addr);
 
    this->m_udpSocketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(m_udpSocketfd == -1){
        ALOGE("Create UDP Client Socket Error Message:%s\n",strerror(errno));
        return -1;
    }

    //设置广播属性
    int op = 1;
    setsockopt(m_udpSocketfd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

    ALOGV("UDP Socket created!\n");
    
    return m_udpSocketfd;
}

//创建一个tcp server socket
int SendClass::createTcpSocket(){
    
    if((m_tcpSocketfd=socket(AF_INET,SOCK_STREAM,0)) < 0){
        ALOGE("Create TCP Server Socket Error Message:%s\n",strerror(errno));
        return -1;
    }

    struct sockaddr_in  sockAddr;
    memset(&sockAddr,0,sizeof(sockAddr));// 各位清零
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_addr.s_addr=INADDR_ANY;
    sockAddr.sin_port=htons(this->udpAndTcpPort);
    if((bind(m_tcpSocketfd,(struct sockaddr*)&sockAddr,sizeof(sockAddr)) < 0)){
        ALOGE("Bind Socket Error Message:%s\n",strerror(errno));
        return -1;
    }

    ALOGV("TCP Socket Created!\n");
}

int SendClass::sendBoardcastMessage(char* sendbuff){
    
    struct sockaddr_in udpClient_addr;
    udpClient_addr.sin_family = AF_INET;
    udpClient_addr.sin_port = htons(this->udpAndTcpPort);
    inet_pton(AF_INET, this->udpBoardcastAddr, &udpClient_addr.sin_addr.s_addr);
 
    int ret = sendto(this->m_udpSocketfd, sendbuff, sizeof(sendbuff), 0, (struct sockaddr*)&udpClient_addr, sizeof(udpClient_addr));
    if(ret < 0){
        ALOGE("Send Boardcast Message Error Message:%s\n",strerror(errno));
        return -1;
    }

    ALOGV("UDP Boardcast Send Success!\n");

    close(this->m_udpSocketfd);

}

//监听tcp连接并接收tcp数据。。
//问题：tcp accept默认是阻塞的。如果使用多线程，主线程用于accept，收到后进入子线程，那么accept是否应该还是阻塞，还是设置成非阻塞？
//accept设置成非阻塞，因为在默认情况下，在使用当前连接的socket和client进行交互的时候，不能够accept新的连接请求。非阻塞之后，有新的连接就可以立刻处理
//当然还是在accept中循环，等待新的链接
void SendClass::listenTcpConnection() {
    
    listen(m_tcpSocketfd, 5);
    ALOGV("Accept Client Tcp Connect......\n");
    //while(1){
        int client_socket_tcp = accept(m_tcpSocketfd, (struct sockaddr*) NULL, NULL);
        if(client_socket_tcp<0){
            ALOGE("Client Connect Failed Error:%s\n",strerror(errno));
        }
        else{
            //解析收到的tcp数据
            char* recvbuff = new char[256];
            recvfrom(this->m_tcpSocketfd, recvbuff, sizeof(recvbuff), 0, NULL, NULL);
            ALOGV("Receive Data From Client: %s\n", recvbuff);

            free(recvbuff);

            close(this->m_tcpSocketfd);
        }
    //}
    
}

int SendClass::getSocketfd(){

    return this->m_udpSocketfd;

}


//void SendClass::setSocketEndPointInfo(SOCKETENDPOINTINFO newVal){
//
//    this->m_socketEndPointInfo = newVal;
//
//}
//
//
//SOCKETENDPOINTINFO SendClass::getSocketEndPointInfo(){
//
//    return this->m_socketEndPointInfo;
//
//}

void SendClass::setUdpBoardcastAddr(char* newVal){

    this->udpBoardcastAddr = newVal;
    ALOGV("Boardcast Addr set to %s\n",this->udpBoardcastAddr);

}

void SendClass::setudpAndTcpPort(int newVal){

    this->udpAndTcpPort = newVal;
    ALOGV("Port set to %d\n",this->udpAndTcpPort);

}