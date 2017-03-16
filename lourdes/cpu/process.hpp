#ifndef __LOURDES_CPU_PROCESS_HPP
#define __LOURDES_CPU_PROCESS_HPP

/// \example    examples/cpu/process.cpp
namespace lourdes { namespace cpu {

class ProcessImpl;

typedef enum
{
    SIGNUM_SIGINT,
    SIGNUM_SIGKILL,
} Signum;

/// \brief  Represents an external running process.
class Process
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    Process();

    /// \brief  Destroys the object and all the associated resources to it.
    ~Process();

    ///	\brief	Starts the process.
    ///	\param	filename	Binary file to be executed.
    ///	\param	arguments	Arguments to be passed to the program.
    ///	\return	A flag that indicates if the program has been executed or not.
    bool run(const char* filename, const char* arguments);

    ///	\brief	Kills the process.
    ///	\return	Indicates if the process was running and has been killed.
    bool signal(Signum signum);

    ///	\brief	Waits until the process has finished.
    ///	\return	Indicates if the process was running and has stopped by itself.
    bool join();

    ///	\brief	Returns a flag that indicates if the process is running.
    ///	\return	Indicates if the process is currently running.
    bool running();

private:
    Process(Process const&);
    Process& operator=(Process const&);
    ProcessImpl* impl;
};

}}

#endif // __LOURDES_CPU_PROCESS_HPP
