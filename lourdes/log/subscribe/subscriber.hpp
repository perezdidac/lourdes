#ifndef __LOURDES_LOG_SUBSCRIBE_SUBSCRIBER_HPP
#define __LOURDES_LOG_SUBSCRIBE_SUBSCRIBER_HPP

/// \brief  Macro that calls lourdes::log::subscribe for subscribing to the logging system.
#define LOG_SUBSCRIBE(x)        lourdes::log::subscribe::subscribe(x)

/// \brief  Macro that calls lourdes::log::subscribe for unsubscribing from the logging system.
#define LOG_UNSUBSCRIBE(x)      lourdes::log::subscribe::unsubscribe(x)

namespace lourdes { namespace log { namespace subscribe {

/// \brief  Interface for subscribing objects to the logger.
class Subscriber
{
public:
    /// \brief  Destroys the object and all the associated resources to it.
    virtual ~Subscriber() { }

    /// \brief  Logs a given message.
    /// \param  message The message that will be logged.
    virtual void log(const char* message) = 0;
};

/// \brief  Subscribes an object to the logger so that all log messages will be
/// redirected.
/// \param  subscriber  An object that has been subclasses from the Subscriber
/// class.
void subscribe(Subscriber* subscriber);

/// \brief  Unsubscribes an object to the logger so that all log messages will
/// not be redirected.
/// \param  subscriber  An object that has been subclasses from the Subscriber
/// class.
void unsubscribe(Subscriber* subscriber);

}}}

#endif // __LOURDES_LOG_SUBSCRIBE_SUBSCRIBER_HPP
