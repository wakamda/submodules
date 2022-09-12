#include "Client.h"
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

#define LOG_TAG "client"

ClientClass::ClientClass(){

}
ClientClass::~ClientClass(){
    
}

//创建udp receive socket
int ClientClass::createUdpSocket(){
    struct sockaddr_in udpRecrive_sock; 
    udpRecrive_sock.sin_family = AF_INET;
    udpRecrive_sock.sin_port = htons(this->udpAndTcpPort);
    udpRecrive_sock.sin_addr.s_addr = INADDR_ANY;

    m_udpSocketfd = socket(AF_INET,SOCK_DGRAM, 0);
    if(m_udpSocketfd < 0){
        ALOGE("Create Socket Error Message:%s\n",strerror(errno));
        return -1;
    }

    int ret = bind(m_udpSocketfd, (struct sockaddr*)&udpRecrive_sock, sizeof(udpRecrive_sock));
    if(ret < 0){
        ALOGE("Bind Socket Error Message:%s\n",strerror(errno));
        return -1;
    }

    ALOGV("Create UDP Socket Success!\n");
    return m_udpSocketfd;
}

int ClientClass::createTcpSocket(){
    
    m_tcpSocketfd=socket(AF_INET,SOCK_STREAM,0);
    if(m_tcpSocketfd <0){
        ALOGE("Create TCP Socket Error Message:%s\n",strerror(errno));
        return -1;
    }
    
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));//各位清零
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_addr.s_addr=inet_addr((this->m_socketEndPointInfo.ip).c_str());  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）
    sockAddr.sin_port=htons(this->udpAndTcpPort);

    int ret = connect(m_tcpSocketfd,(struct sockaddr*)&sockAddr,sizeof(sockAddr));
    if(ret < 0)
    {
        ALOGE("Connect Server Error Message:%s\n",strerror(errno));
        return -1;
    }

    ALOGV("Create Tcp Socket Success!\n");
    return m_tcpSocketfd;
}

//接收udp client信息，解析获得ip和port
SOCKETENDPOINTINFO ClientClass::recvUdpMessageAndParse(int socketfd){
    int option_value;
	socklen_t  length;
    char * recvBuffer =new char[1024];

    struct sockaddr_in udpClient_addr;
	socklen_t addrlen = sizeof(udpClient_addr);
	
    
    //将数据写入recvBuffer
	int len=recvfrom(socketfd,recvBuffer,sizeof(recvBuffer),0,(struct sockaddr*)&udpClient_addr,&addrlen);

	if (len < 0)
	{
		int ret = getsockopt(socketfd, SOL_SOCKET, SO_ERROR, &option_value, &length );
		if(ret < 0){
            ALOGE("Receive Data Error Message:%s\n",strerror(errno));
            exit(1);
        }
	}
    ALOGV("Receive Data:%s\n",recvBuffer);

    //将sockaddr结构转换成string和int
	this->m_socketEndPointInfo.ip = inet_ntoa(udpClient_addr.sin_addr);
	this->m_socketEndPointInfo.port = ntohs(udpClient_addr.sin_port);

	ALOGV("Service Provider Ip:%s\n",inet_ntoa(udpClient_addr.sin_addr));
    ALOGV("Service Provider Port:%d\n",this->m_socketEndPointInfo.port);

    close(this->m_udpSocketfd);
    return this->m_socketEndPointInfo;
}

int ClientClass::sendTcpMessage(char* sendbuff){
    int ret = send(this->m_tcpSocketfd,sendbuff,sizeof(sendbuff),0);
    if((ret)<0)
    {
        ALOGE("Send Data Error Message:%s\n",strerror(errno));
        return -1;
    }
    ALOGV("Send Tcp Data Success!\n");

    close(this->m_tcpSocketfd);
}

int ClientClass::getUdpSocketfd(){

    return this->m_udpSocketfd;

}


void ClientClass::setSocketEndPointInfo(SOCKETENDPOINTINFO newVal){

    this->m_socketEndPointInfo = newVal;

}


SOCKETENDPOINTINFO ClientClass::getSocketEndPointInfo(){

    return this->m_socketEndPointInfo;

}

void ClientClass::setUdpAndTcpPort(int newVal){

    this->udpAndTcpPort = newVal;
    ALOGV("Port set to %d\n",this->udpAndTcpPort);

}
