#pragma once
#include "List.hpp"
#include "tcb.hpp"

class semaphore {

public:
    void signal();
    void wait();

    explicit semaphore(int initValue);
private:
    int value = 0;
    static List<TCB> blockedQueue;

};
