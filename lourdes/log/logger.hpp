#ifndef __LOURDES_LOG_LOG_HPP
#define __LOURDES_LOG_LOG_HPP

/// \brief  Macro that calls lourdes::log::init for initializing the logging system.
#define LOG_INIT(...)           lourdes::log::init(__VA_ARGS__)

/// \brief  Macro that calls lourdes::log::debug for logging a message with DEBUG log level.
#define LOG_DEBUG(x, ...)       lourdes::log::debug(x, ## __VA_ARGS__)

/// \brief  Macro that calls lourdes::log::info for logging a message with INFO log level.
#define LOG_INFO(x, ...)        lourdes::log::info(x, ## __VA_ARGS__)

/// \brief  Macro that calls lourdes::log::warning for logging a message with WARNING log level.
#define LOG_WARNING(x, ...)     lourdes::log::warning(x, ## __VA_ARGS__)

/// \brief  Macro that calls lourdes::log::error for logging a message with ERROR log level.
#define LOG_ERROR(x, ...)       lourdes::log::error(x, ## __VA_ARGS__)

/// \brief  Macro that calls lourdes::log::critical for logging a message with CRITICAL log level.
#define LOG_CRITICAL(x, ...)    lourdes::log::critical(x, ## __VA_ARGS__)

namespace lourdes { namespace log {

/// \brief  Contains the possible log level values for both file and standard
/// error.
typedef enum
{
    LOG_LEVEL_DEBUG     = 0,    ///<    The most verbose debug level. Must be used for debugging purposes.
    LOG_LEVEL_INFO      = 1,    ///<    Default debug level, used for notifications and regular messages.
    LOG_LEVEL_WARNING   = 2,    ///<    Must be used when something is could be wrong and the administrator should take a look.
    LOG_LEVEL_ERROR     = 3,    ///<    Must be used for situations in which the administrator must take a look quickly.
    LOG_LEVEL_CRITICAL  = 4,    ///<    Must be used for critical situations in which the system could get down.
    LOG_LEVEL_DISABLED  = 5,    ///<    Used for disabling the log system.
} LogLevel;

/// \brief  Initializes the Singleton-based log class.
/// \param  app             Application name, which will be used for the log
/// file name.
/// \param  directory       Directory in which the log files will be saved.
/// \param  fileLogLevel    Indicates the log level for the file output.
/// \param  outLogLevel     Indicates the log level for the standard error.
void init(const char* app, const char* directory, LogLevel fileLogLevel, LogLevel outLogLevel);

/// \brief  Logs a message with DEBUG log level.
/// \param  fmt A printf-based string.
/// \param  ... Extra parameters that must be included in the printf-based
/// message.
void debug(const char* fmt, ...);

/// \brief  Logs a message with INFO log level.
/// \param  fmt A printf-based string.
/// \param  ... Extra parameters that must be included in the printf-based
/// message.
void info(const char* fmt, ...);

/// \brief  Logs a message with WARNING log level.
/// \param  fmt A printf-based string.
/// \param  ... Extra parameters that must be included in the printf-based
/// message.
void warning(const char* fmt, ...);

/// \brief  Logs a message with ERROR log level.
/// \param  fmt A printf-based string.
/// \param  ... Extra parameters that must be included in the printf-based
/// message.
void error(const char* fmt, ...);

/// \brief  Logs a message with CRITICAL log level.
/// \param  fmt A printf-based string.
/// \param  ... Extra parameters that must be included in the printf-based
/// message.
void critical(const char* fmt, ...);

}}

#endif // __LOURDES_LOG_LOG_HPP
