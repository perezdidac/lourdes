#include "output.hpp"

#include "../chrono/datetime.hpp"
#include "../cpu/mutex.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

namespace lourdes { namespace log { namespace subscribe {

void Output::log(const char* message)
{
    char log_level[256];
    char log_file[256];

    // Prepare the current time formatted as a string
    char datetime[256];
    char date[256];
    lourdes::chrono::universal("%Y-%m-%d %H:%M:%S", datetime);
    lourdes::chrono::universal("%Y%m%d", date);

    sprintf(log_file, "%s/%s_%s.log", logger.directory, logger.app, date);

    // Open the log file
    switch (logLevel)
    {
    case LOG_LEVEL_DEBUG:
        strcpy(log_level, "DEBG");
        break;
    case LOG_LEVEL_INFO:
        strcpy(log_level, "INFO");
        break;
    case LOG_LEVEL_WARNING:
        strcpy(log_level, "WARN");
        break;
    case LOG_LEVEL_ERROR:
        strcpy(log_level, "ERRO");
        break;
    case LOG_LEVEL_CRITICAL:
        strcpy(log_level, "CRIT");
        break;
    default:
        return;
    }

    logger.lock();

    // Write message to stderr
    fprintf(stderr, "[%s]\t%s:\t%s\n", datetime, log_level, message);

    FILE* logFile = fopen(log_file, "a");
    if (logFile == NULL)
    {
        logger.unlock();
        return;
    }

    // Write the message to the log file
    fprintf(logFile, "[%s]\t%s:\t%s\n", datetime, log_level, message);
    fclose(logFile);

    logger.unlock();
}

}}}
