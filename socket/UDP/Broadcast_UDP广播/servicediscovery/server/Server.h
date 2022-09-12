#ifndef SEND_H
#define SEND_H
#include <string>

typedef struct 
{
    std::string ip;
    int port;
}SOCKETENDPOINTINFO;


class SendClass{
public:
    SendClass();
    ~SendClass();

    int createUdpSocket();

    int createTcpSocket();

    int sendBoardcastMessage(char* sendbuff);

    void listenTcpConnection();
    

/************data hiden****************/
    
    int getSocketfd();

    void setudpAndTcpPort(int newVal);

    int getudpAndTcpPortt();

    void setUdpBoardcastAddr(char* newVal);

private:

    int m_udpSocketfd;

    int m_tcpSocketfd;

    int udpAndTcpPort;

    char* udpBoardcastAddr;
};


#endif //SEND_H