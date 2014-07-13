/* © Copyright 2013 jingmi. All Rights Reserved.
 *
 * +----------------------------------------------------------------------+
 * | Log library implementation                                           |
 * +----------------------------------------------------------------------+
 * | Author: jingmi@gmail.com                                             |
 * +----------------------------------------------------------------------+
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "log.h"

#define LOG_SIZE (8192)
#define MAX_LOG_PATH PATH_MAX

struct log_file
{
    pthread_mutex_t lock;
    int fd;
    char log_path[MAX_LOG_PATH];
};

static log_file_t *g_log_file = NULL;

log_file_t *get_global_log()
{
    return g_log_file;
}

log_file_t *common_log_open(const char *log_path)
{
    struct stat sb;

    log_file_t *file = (log_file_t*)malloc(sizeof (log_file_t));
    if (file == NULL)
    {
        return NULL;
    }

    //deepcopy log_path
    size_t max_size = sizeof(file->log_path) - 1;
    size_t l = strlen(log_path);
    size_t need_size = l < max_size ? l : max_size;
    strncpy(file->log_path, log_path, need_size);
    file->log_path[need_size] = '\0';

    file->fd = -1;
    pthread_mutex_init(&(file->lock), NULL);

    if (stat(file->log_path, &sb) == 0)
    {
        if (S_ISREG(sb.st_mode))
            file->fd = open(file->log_path, O_APPEND|O_RDWR);
        else
            goto ret;
    }
    else
    {
        file->fd = open(file->log_path, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IROTH|S_IRGRP);
    }

ret:
    if (file->fd >= 0)
        return file;
    else
        pthread_mutex_destroy(&(file->lock));
        free(file);
        return NULL;
}

int log_open(const char *log_path)
{
    log_file_t *file = common_log_open(log_path);
    if (file == NULL)
    {
        return -1;
    }
    g_log_file = file;
    return 0;
}

int common_log_mesg(log_file_t* file, const char *codefile, int linenum, uint32_t mesg_level, const char *fmt, ...)
{
    char line[LOG_SIZE];
    va_list ap;
    char *level;
    time_t now;
    struct tm t;
    char time_string[30];
    int printed_len;

    switch (mesg_level)
    {
    case LOG_LEVEL_DEBUG:
        level = "debug";
        break;
    case LOG_LEVEL_WARN:
        level = "warn";
        break;
    case LOG_LEVEL_ERROR:
        level = "error";
        break;
    case LOG_LEVEL_NOTICE:
        level = "notice";
        break;
    default:
        level = "what's this";
        break;
    }
    now = time(NULL);
    localtime_r(&now, &t);
    snprintf(time_string, sizeof time_string, "%d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    va_start(ap, fmt);
    printed_len = snprintf(line, sizeof(line), "[%s] [%s] (%s:%d) ", time_string, level, codefile, linenum);
    printed_len += vsnprintf(line + printed_len, sizeof(line) - printed_len, fmt, ap);
    va_end(ap);
    if (printed_len >= LOG_SIZE - 1)
    {
        /* XXX: to avoid stack overflow */
        printed_len = LOG_SIZE - 2;
    }
    line[ printed_len ] = '\n';
    line[ printed_len + 1 ] = '\0';
    pthread_mutex_lock(&(file->lock));
    ssize_t nwrite = write(file->fd, line, strlen(line));
    (void)nwrite;
    pthread_mutex_unlock(&(file->lock));

    return 0;
}

int common_log_close(log_file_t *file)
{
    pthread_mutex_destroy(&(file->lock));
    close(file->fd);
    file->fd = -1;
    free(file);
    return 0;
}
/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker: */
