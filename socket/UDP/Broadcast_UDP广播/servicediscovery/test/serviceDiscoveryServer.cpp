#include "../server/Server.h"
#include "../clog/Log.h"
#include <unistd.h>

typedef enum{
    LOG_VERBOSE    = 0x00, /*!< VERBOSE */
    LOG_DEBUG      = 0x01, /*!< DEBUG  */
    LOG_INFO       = 0x03, /*!< INFO  */ 
    LOG_WARN       = 0x04, /*!< WARN  */
    LOG_ERROR      = 0x05, /*!< ERROR  */
    LOG_FATAL      = 0x06, /*!< FATAL  */
}DoipLogLevel_t;

int GetLogLevel(void){
     return log_get_level();
}

int SetLogLevel(int level){
     return log_set_level((Log_Level_t)level);
}

int parse_opt(int argc,  char * const argv[]){
	int c;
	while ((c = getopt (argc, argv, "v")) != -1){
		switch (c){
			case 'v':
				SetLogLevel( GetLogLevel() - 1 );
				break;
			default:
				break;
		}

	}
	return 0;
}


int main(int argc, char * const argv[])
{
    SetLogLevel(LOG_ERROR);
    parse_opt(argc, argv);

    char* a = "abc";
    SendClass server;

    server.setudpAndTcpPort(58580);
    server.setUdpBoardcastAddr("172.20.10.15");

    server.createUdpSocket();

    //for(int i = 0;i<10;i++){
        if(server.sendBoardcastMessage(a)<0){
            return -1;
        }
    //}

    server.createTcpSocket();

    server.listenTcpConnection();

    return 0;
}
