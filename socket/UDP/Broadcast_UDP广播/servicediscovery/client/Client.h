#ifndef CLIENT_H
#define CLIENT_H
#include <string>

typedef struct 
{
    std::string ip;
    int port;
}SOCKETENDPOINTINFO;

class ClientClass{
public:
    ClientClass();
    ~ClientClass();

    
    int createUdpSocket();

    int createTcpSocket();

    /**
     * @brief 接收udp send的信息，解析获得ip和port
     * 
     * @param socketfd 
     * @return SOCKETENDPOINTINFO 
     */
    SOCKETENDPOINTINFO recvUdpMessageAndParse(int socketfd);    


    int sendTcpMessage(char* sendbuff);
    

/************data hiden****************/
    
    int getUdpSocketfd();

    
    void setSocketEndPointInfo(SOCKETENDPOINTINFO infnewValo);

    
    SOCKETENDPOINTINFO getSocketEndPointInfo();

    void setUdpAndTcpPort(int newVal);

private:

    int m_udpSocketfd;

    int m_tcpSocketfd;

    SOCKETENDPOINTINFO m_socketEndPointInfo;

    int udpAndTcpPort;

};

#endif //CLIENT_H