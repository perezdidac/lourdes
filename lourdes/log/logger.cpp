#include "logger.hpp"

#include "../chrono/datetime.hpp"
#include "../cpu/mutex.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

namespace lourdes { namespace log {

/// \brief  Singleton-based logger class.
class Logger
{
public:
    /// \brief  Static method for getting the Singleton unique instance of the logger.
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    /// \brief  Locks the mutual exclusion object for writting the log message.
    void lock()
    {
        mutex.lock();
    }

    /// \brief  Frees the mutual exclusion object for writting the log message.
    void unlock()
    {
        mutex.unlock();
    }

private:
    Logger()
    {
        strcpy(app, "");
        strcpy(directory, "");
        minFileLogLevel = LOG_LEVEL_DISABLED;
        minOutLogLevel = LOG_LEVEL_DISABLED;
    }
    Logger(Logger const&);
    void operator=(Logger const&);

private:
    lourdes::cpu::Mutex mutex;

public:
    char app[255];
    char directory[255];
    LogLevel minFileLogLevel;
    LogLevel minOutLogLevel;
};

void log(LogLevel logLevel, const char* message)
{
    Logger& logger = Logger::getInstance();

    if (logLevel < logger.minFileLogLevel && logLevel < logger.minOutLogLevel)
        return;

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

void init(const char* app, const char* directory, LogLevel fileLogLevel, LogLevel outLogLevel)
{
    Logger& logger = Logger::getInstance();

    // Save app name
    strcpy(logger.app, app);
    strcpy(logger.directory, directory);
    logger.minFileLogLevel = fileLogLevel;
    logger.minOutLogLevel = outLogLevel;
}

void debug(const char* fmt, ...)
{
    char message[1024];

    // Format the original message
    va_list arg;
    va_start(arg, fmt);
    vsprintf(message, fmt, arg);
    va_end(arg);

    log(LOG_LEVEL_DEBUG, message);
}

void info(const char* fmt, ...)
{
    char message[1024];

    // Format the original message
    va_list arg;
    va_start(arg, fmt);
    vsprintf(message, fmt, arg);
    va_end(arg);

    log(LOG_LEVEL_INFO, message);
}

void warning(const char* fmt, ...)
{
    char message[1024];

    // Format the original message
    va_list arg;
    va_start(arg, fmt);
    vsprintf(message, fmt, arg);
    va_end(arg);

    log(LOG_LEVEL_WARNING, message);
}

void error(const char* fmt, ...)
{
    char message[1024];

    // Format the original message
    va_list arg;
    va_start(arg, fmt);
    vsprintf(message, fmt, arg);
    va_end(arg);

    log(LOG_LEVEL_ERROR, message);
}

void critical(const char* fmt, ...)
{
    char message[1024];

    // Format the original message
    va_list arg;
    va_start(arg, fmt);
    vsprintf(message, fmt, arg);
    va_end(arg);

    log(LOG_LEVEL_CRITICAL, message);
}

}}
