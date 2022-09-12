#include "socketcommon.h"
#include "../../log/Log.h"

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>//linux下特有的头文件，主要包含了read，write等函数
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

SocketCommonClass::SocketCommonClass(){

}

SocketCommonClass::~SocketCommonClass(){

}

int SocketCommonClass::createSocket(){
    
}