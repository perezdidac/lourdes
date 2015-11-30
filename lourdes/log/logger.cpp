#include "logger.hpp"

#include "../cpu/mutex.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Boost includes
#include <boost/date_time.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _WIN32
// List of colors
#define KNRM    "\x1B[0m"
#define KRED    "\x1B[31m"
#define KGRN    "\x1B[32m"
#define KYEL    "\x1B[33m"
#define KBLU    "\x1B[34m"
#define KMAG    "\x1B[35m"
#define KCYN    "\x1B[36m"
#define KWHT    "\x1B[37m"
#define RESET   "\033[0m"
#endif

namespace lourdes { namespace log {

/// \brief  Singleton-based logger class.
class Log
{
public:
    /// \brief  Static method for getting the Singleton unique instance of the logger.
    static Log& getInstance()
    {
        static Log instance;
        return instance;
    }

private:
    Log()
    {
        strcpy(app, "");
        strcpy(directory, "");
        minFileLogLevel = LOG_LEVEL_DISABLED;
        minOutLogLevel = LOG_LEVEL_DISABLED;
    }
    Log(Log const&);
    void operator=(Log const&);

public:
    lourdes::cpu::Mutex logMutex;
    lourdes::cpu::Mutex outMutex;
    char app[255];
    char directory[255];
    LogLevel minFileLogLevel;
    LogLevel minOutLogLevel;
};

void log(LogLevel logLevel, const char* message)
{
    Log& logger = Log::getInstance();

    if (logLevel < logger.minFileLogLevel)
        return;

    char log_level[256];
    char log_file[256];

    // Prepare the current time formatted as a string
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::universal_time();
    std::stringstream stream;
    std::stringstream streamFilename;
    stream.imbue(std::locale(stream.getloc(), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S")));
    streamFilename.imbue(std::locale(streamFilename.getloc(), new boost::posix_time::time_facet("%Y%m%d")));
    stream << currentTime;
    streamFilename << currentTime;
    std::string strTime = stream.str();
    std::string strTimeFile = streamFilename.str();

    sprintf(log_file, "%s/%s_%s.log", logger.directory, logger.app, strTimeFile.c_str());

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

    logger.logMutex.lock();

    FILE* logFile = fopen(log_file, "a");
    if (logFile == NULL)
    {
        logger.logMutex.unlock();
        return;
    }

    // Write the message to the log file
    fprintf(logFile, "[%s]\t%s:\t%s", strTime.c_str(), log_level, message);
    fclose(logFile);

    logger.logMutex.unlock();
}

void out(LogLevel logLevel, const char* message)
{
    Log& logger = Log::getInstance();

    if (logLevel < logger.minOutLogLevel)
        return;

    char log_level[256];

    // Prepare the current time formatted as a string
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::universal_time();
    std::stringstream stream;
    stream.imbue(std::locale(stream.getloc(), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S")));
    stream << currentTime;
    std::string strTime = stream.str();

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

    logger.outMutex.lock();
    fprintf(stderr, "[%s]\t%s:\t%s", strTime.c_str(), log_level, message);
    logger.outMutex.unlock();
}

void init(const char* app, const char* directory, LogLevel fileLogLevel, LogLevel outLogLevel)
{
    Log& logger = Log::getInstance();

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
    out(LOG_LEVEL_DEBUG, message);
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
    out(LOG_LEVEL_INFO, message);
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
    out(LOG_LEVEL_WARNING, message);
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
    out(LOG_LEVEL_ERROR, message);
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
    out(LOG_LEVEL_CRITICAL, message);
}

}}
