#pragma once
#include "List.hpp"
class TCB;
class Scheduler {
private:
    static List<TCB> readyContinueQueue;
public:
    static TCB* get();
    static void put(TCB* ccb);
};