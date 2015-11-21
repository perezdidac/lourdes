#ifndef __LOURDES_THREAD_HPP
#define __LOURDES_THREAD_HPP

namespace lourdes
{

class ThreadImpl;

class Thread
{
public:
    Thread();
    virtual ~Thread();

    void start();
    void join();

private:
    static void threadStart(Thread* This);

protected:
    virtual void run() = 0;
    
private:
    ThreadImpl* impl;
};

}

#endif // __LOURDES_THREAD_HPP
