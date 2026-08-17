#pragma once
#include "syscall_c.hpp"

class Thread {
private:
    thread_t myHandle;
    void (*body)(void*);
    void* bodyArg;

    static void wrapper(void* arg);

protected:
    virtual void run();

public:
    Thread();
    Thread(void (*body)(void*), void* arg);
    virtual ~Thread();

    int start();
    static void dispatch();
    static int exit();
};