#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include "Log.h"
#define LOG_BUF_SIZE (1024*9)
static char g_log_buffer[LOG_BUF_SIZE];
static int g_log_level = PRIO_LOG_INFO;

//
static const char* RED = "\033[31m";
static const char* YELLOW = "\033[33m";
static const char* GREEN = "\033[32m";
static const char* RESET = "\033[0m";

static const char* level_to_str(int _level){

	switch(_level){
		case PRIO_LOG_VERBOSE: return "TRACE";
		case PRIO_LOG_DEBUG: return "DEBUG";
        case PRIO_LOG_INFO: return "INFO";
		case PRIO_LOG_WARN: return "WARN" ;
		case PRIO_LOG_ERROR: return "ERROR";
        case PRIO_LOG_FATAL: return "FATAL";
		default:
			return "UNDEF";
	}
}


int log_set_level(Log_Level_t level){
    if( (PRIO_LOG_VERBOSE<=level) && (level <= PRIO_LOG_FATAL)){
        g_log_level = level;
    }
    return g_log_level;
}
int log_get_level(){
    return g_log_level;
}

//
//
__attribute__((weak)) void LogWriteStr(int level, const char * tag, const char*log){
    time_t when;
    struct tm* ptm;
    char timeBuf[32];
    time(&when);
    ptm = localtime(&when);
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", ptm);
    switch(level){
		case PRIO_LOG_VERBOSE: std::cerr <<"["<< timeBuf<<"] " ;break;
		case PRIO_LOG_DEBUG:   std::cerr <<"["<< timeBuf<<"] " ;std::cerr << GREEN; break;
        case PRIO_LOG_INFO:    std::cerr <<"["<< timeBuf<<"] " ;std::cerr << GREEN; break;
		case PRIO_LOG_WARN:    std::cerr <<"["<< timeBuf<<"] " ;std::cerr << YELLOW; break;
		case PRIO_LOG_ERROR:   std::cerr <<"["<< timeBuf<<"] " ;std::cerr << RED; break;
        case PRIO_LOG_FATAL:   std::cerr <<"["<< timeBuf<<"] " ;std::cerr << RED; break;
		default:
			break;
	}

    std::cerr << "<" << level_to_str(level) << ">";
    std::cerr << "[ " << tag << " ] " ;
    std::cerr << log << RESET << std::endl;
}

//
//
__attribute__((weak))  void LogWriteHex(int level, const char * tag, const char* desc, const void* hex, int len){
    const char * _hex = (const char*)hex;
    std::memset(g_log_buffer, 0, sizeof(g_log_buffer));
    int n =  snprintf(g_log_buffer, sizeof(g_log_buffer), "%s\n", desc);
    for(int i = 0; i < len; ++i){
        if( (i%16) == 0){
            n += snprintf(g_log_buffer + n, sizeof(g_log_buffer)-n, "%s%04X: %02X ", i == 0 ? "\t\t\t":"\n\t\t\t", (i/15) + 1, (unsigned char)_hex[i]);
        }else{
            n += snprintf(g_log_buffer + n, sizeof(g_log_buffer)-n, "%02X ", (unsigned char)_hex[i]);
        }
        
    }
    n += snprintf(g_log_buffer + n, sizeof(g_log_buffer)-n, "\n");
    LogWriteStr(level, tag, g_log_buffer);
}


//
int ___log_print(int prio, const char *tag, const char *fmt, ...)
{
    //
    if(prio < g_log_level ){
        return 0;
    }

    //
    va_list ap;
    //
    va_start(ap, fmt);
    //init buff
    memset(g_log_buffer, 0,  sizeof(g_log_buffer));
    //
    vsnprintf(g_log_buffer, sizeof(g_log_buffer), fmt, ap);
    //
    va_end(ap);

    LogWriteStr(prio, tag, g_log_buffer);
    
    return 0;
}

//
int ___log_print_hex(int prio, const char *tag, const char* desc, const void* hex, int length){
    if(prio < g_log_level ){
        return 0;
    }
    LogWriteHex(prio, tag, desc, hex, length);
    
    return 0;
}
