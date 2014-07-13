#include <cstdlib>
//#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
//#include <log4cplus/helpers/loglog.h>
//#include <log4cplus/helpers/stringhelper.h>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

int main()
{
    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./conf/log4cplus.properties"));
    Logger logger = Logger::getRoot();

    for (int i = 0; i < 20000; i++) {
        // trace
        LOG4CPLUS_TRACE(logger, "trace and get the fingerprint: " << "random integer: "<< random());

        // debug
        LOG4CPLUS_DEBUG(logger, "this is debug log: " << "random integer: "<< random());

        // info
        LOG4CPLUS_INFO(logger, "the information centry...." << "[ 1 + 1 = " << 1 + 1 << "]");

        // warn
        LOG4CPLUS_WARN(logger, "Writing warning messages to log....");

        // error
        LOG4CPLUS_ERROR(logger, "ooooooh, there is an error....");

        //fatal
        LOG4CPLUS_FATAL(logger, "oh, my god! the fatal error occur!!!!!!!!!");
    }

    return 0;
}
