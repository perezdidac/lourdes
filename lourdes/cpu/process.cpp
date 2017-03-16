#include "process.hpp"

#ifndef _WIN32
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#else
#include <Windows.h>
#include <stdio.h>
#endif

namespace lourdes { namespace cpu {

class ProcessImpl
{
public:
#ifndef _WIN32
    int pid;
#else
    void* hProcess;
    void* hThread;
#endif
};

Process::Process()
{
    impl = new ProcessImpl;
}

Process::~Process()
{
    delete impl;
}

bool Process::run(const char* filename, const char* arguments)
{
    // Check if the process is currently running
    if (running())
        return false;

    // Try to launch the process
#ifndef _WIN32

    //TODO: fix that!
    pid = fork();
    if (pid == 0)
    {
        // Child process
        execvp(filename.c_str(), arguments);
        _exit(0);
    }
    return pid > 0;

#else

    STARTUPINFO info;
    ZeroMemory(&info, sizeof(STARTUPINFO));
    info.cb = sizeof(STARTUPINFO);
    info.hStdError = NULL;
    info.hStdOutput = NULL;
    info.dwFlags |= STARTF_USESTDHANDLES;
    PROCESS_INFORMATION processInfo;

    char commandLine[1024];
    sprintf(commandLine, "%s %s", filename, arguments);
    if (!CreateProcess(filename, commandLine, NULL, NULL, TRUE, 0, NULL, NULL,
            &info, &processInfo))
        return false;

    impl->hProcess = processInfo.hProcess;
    impl->hThread = processInfo.hThread;
    return true;

#endif
}

bool Process::signal(Signum signum)
{
    // Check if the process is currently running
    if (!running())
        return false;

    // Kill the process
#ifndef _WIN32
    // Choose the right signal number
    int sig = SIGINT;
    if (signum == SIGNUM_SIGKILL)
        signum = SIGNUM_SIGKILL;

    ::kill(pid, sig);
    wait(NULL);
    pid = 0;
#else
    TerminateThread(impl->hThread, 0);
    TerminateProcess(impl->hProcess, 0);
    impl->hProcess = NULL;
    impl->hThread = NULL;
#endif

    return true;
}

bool Process::join()
{
    // Check if the process is currently running
    if (!running())
        return false;

    // Wait until the process ends
#ifndef _WIN32
    int status;
    waitpid(pid, &status, 0);
    pid = 0;
#else
    WaitForSingleObject(impl->hProcess, INFINITE);
    CloseHandle(impl->hProcess);
    CloseHandle(impl->hThread);
    impl->hProcess = NULL;
    impl->hThread = NULL;
#endif

    return true;
}

bool Process::running()
{
#ifndef _WIN32
    if (pid == 0)
        return false;

    int status;
    pid_t result = waitpid(pid, &status, WNOHANG);
    if (result == 0)
        return true;
    else
        return false;
#else
    if (impl->hProcess == NULL)
        return false;

    DWORD exitCode = NULL;
    if (GetExitCodeProcess(impl->hProcess, &exitCode))
    {
        if (exitCode == STILL_ACTIVE)
            return true;
    }
    impl->hProcess = NULL;
    impl->hThread = NULL;
    return false;

#endif
}

}}
