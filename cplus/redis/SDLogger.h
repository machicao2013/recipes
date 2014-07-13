#ifndef SANDAI_C_LOGGER_H_200508162107
#define SANDAI_C_LOGGER_H_200508162107

#ifdef LOGGER
//#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#define DECL_LOGGER(logger) static log4cplus::Logger logger;
#define IMPL_LOGGER(classname, logger) log4cplus::Logger classname::logger = log4cplus::Logger::getInstance(#classname);

#ifndef _DEBUG

#ifdef LOG4CPLUS_DEBUG
#undef LOG4CPLUS_DEBUG
#define LOG4CPLUS_DEBUG(a,b)
#endif

#ifdef LOG4CPLUS_INFO
#undef LOG4CPLUS_INFO
#define LOG4CPLUS_INFO(a,b)
#endif

#endif // #ifndef _DEBUG

#else  // #ifdef LOGGER
#define _LOG4CPLUS_LOGGING_MACROS_HEADER_
#define LOG4CPLUS_DEBUG(a,b)
#define LOG4CPLUS_INFO(a,b)
#define LOG4CPLUS_WARN(a,b)
#define LOG4CPLUS_ERROR(a,b)
#define LOG4CPLUS_FATAL(a,b)

#define DECL_LOGGER(logger)
#define IMPL_LOGGER(classname, logger)

#endif

#endif

