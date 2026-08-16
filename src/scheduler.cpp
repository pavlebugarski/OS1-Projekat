//
// Created by os on 8/13/26.
#include "../h/scheduler.hpp"

List<TCB> Scheduler::readyContinueQueue;

TCB *Scheduler::get() {
    return readyContinueQueue.removeFirst();
};

void Scheduler::put(TCB *ccb) {
    readyContinueQueue.addLast(ccb);
}
