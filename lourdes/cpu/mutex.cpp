#include "mutex.hpp"

#include <boost/thread.hpp>

namespace lourdes { namespace cpu {

class MutexImpl
{
public:
    boost::mutex mutex;
};

Mutex::Mutex()
{
    impl = new MutexImpl;
}

Mutex::~Mutex()
{
    delete impl;
}

void Mutex::lock()
{
    impl->mutex.lock();
}

void Mutex::unlock()
{
    impl->mutex.unlock();
}

}}
