#pragma once
#include "List.hpp"
#include "tcb.hpp"
class Scheduler {
private:
    static List<CCB> readyContinueQueue;
public:
    static CCB* get();
    static void put(CCB* ccb);
}