#ifndef CMYTASK_H
#define CMYTASK_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "../Thread/Thread.h"

 
class CMyTask: public CTask 
{   
 public:
    CMyTask() = default;    
    int Run();
};

#endif //CMYTASK_H