#ifndef __LOURDES_LOG_SUBSCRIBE_OUTPUT_HPP
#define __LOURDES_LOG_SUBSCRIBE_OUTPUT_HPP

#include "subscriber.hpp"

namespace lourdes { namespace log { namespace subscribe {

/// \brief  Log subscriber that logs to stderr.
class Output : public Subscriber
{
public:
    /// \brief  Logs a given message.
    /// \param  message The message that will be logged.
    void log(const char* message);
};

}}}

#endif // __LOURDES_LOG_SUBSCRIBE_OUTPUT_HPP
