#include <stdio.h>
#include "logger.h"
#include <stdarg.h>
#include <string.h>
#include <syslog.h>

int logFlag = 0;

int initLogger(char *logType) {
    
    if (strcmp(logType,"stdout") == 0) {
        logFlag = 0;
    } else if (strcmp(logType,"syslog") == 0) {
        logFlag = 1;
    } else {
        printf("Initializing Logger on: %s\n", logType);
        return 0;
    }
    return 1;
    
}

int infof(const char *format, ...) {
    
    va_list args;
    va_start (args, format);
    
    if (logFlag == 1) {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_INFO,format, args);
        closelog();

    } else {
        printf("info: ");
        vprintf(format, args);
    }
    
    va_end(args);
    return 0;
}

int warnf(const char *format, ...) {

    va_list args;
    va_start (args, format);

    if (logFlag == 1) {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_WARNING,format, args);
        closelog();

    } else {
        printf("warning: ");
        vprintf(format, args);
    }
    
    va_end(args);
    return 0;
}

int errorf(const char *format, ...) {

    va_list args;
    va_start (args, format);

    if (logFlag == 1) {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_ERR,format, args);
        closelog();

    } else {
        printf("error: ");
        vprintf(format, args);
    }  

    va_end(args);
    return 0;
}
int panicf(const char *format, ...) {

    va_list args;
    va_start (args, format);

    if (logFlag == 1) {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, args);
        closelog();

    } else {
        printf("panic: ");
        vprintf(format, args);    
    }
    
    va_end(args);
    return 0;
}
