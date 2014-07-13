#include <stdio.h>
#include <stdarg.h>

const int REDIS_MAX_LOGMSG_LEN = 1024;

void redisLog(int level, const char *fmt, ...)
{
    va_list ap;
    char msg[REDIS_MAX_LOGMSG_LEN];
    if ((level&0xff) < server.verbosity)
        return;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    redisLogRaw(level,msg);
}
