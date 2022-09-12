#ifndef SOCKETCOMMON_H
#define SOCKETCOMMON_H

class SocketCommonClass{
public:
    SocketCommonClass();
    ~SocketCommonClass();
    
    int createSocket();

    int setSocketField();

    int connectSocket();

    int send();

    int sendTo();

private:
    int socket;


};

#endif //SOCKETCOMMON_H