#ifndef _LOG_H_
#define _LOG_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG_LEVEL_DEBUG   0x1
#define LOG_LEVEL_WARN    0x2
#define LOG_LEVEL_ERROR   0x4
#define LOG_LEVEL_NOTICE  0x8

typedef struct log_file log_file_t;

log_file_t *get_global_log();

#define log_debug(fmt, ...)  common_log_mesg(get_global_log(),  __FILE__, __LINE__, LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define log_notice(fmt, ...) common_log_mesg(get_global_log(), __FILE__, __LINE__, LOG_LEVEL_NOTICE, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)   common_log_mesg(get_global_log(), __FILE__, __LINE__, LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)  common_log_mesg(get_global_log(), __FILE__, __LINE__, LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define log_close() common_log_close(get_global_log())

#define user_log_open(log_path) common_log_open(log_path)
#define user_log_debug(p_log_file, fmt, ...)  common_log_mesg(p_log_file, __FILE__, __LINE__, LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define user_log_notice(p_log_file, fmt, ...) common_log_mesg(p_log_file, __FILE__, __LINE__, LOG_LEVEL_NOTICE, fmt, ##__VA_ARGS__)
#define user_log_warn(p_log_file, fmt, ...)   common_log_mesg(p_log_file, __FILE__, __LINE__, LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define user_log_error(p_log_file, fmt, ...)  common_log_mesg(p_log_file, __FILE__, __LINE__, LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define user_log_close(p_log_file) common_log_close(p_log_file)

log_file_t *common_log_open(const char *log_path);
int log_open(const char *log_path);
int common_log_mesg(log_file_t *file, const char *codefile, int linenum, uint32_t mesg_level, const char *fmt, ...) __attribute__ ((format (printf, 5, 6)));
int common_log_close(log_file_t *file);



#ifdef __cplusplus
}
#endif

#endif /* ! _LOG_H_ */
/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker: */
