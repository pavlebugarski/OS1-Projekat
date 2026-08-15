//
// Created by os on 8/13/26.
#include "../h/scheduler.hpp"

List <TCB>:: Scheduler readyCoroutineQueue;

TCB *Scheduler::get() {
    return readyCoroutineQueue.removeFirst();
};

void Scheduler::put(CCB *ccb) {
    readyContinueQueue.addLast(ccb);
}
