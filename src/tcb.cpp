//
// Created by os on 8/12/26.
//
#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/scheduler.hpp"

TCB* TCB::running = nullptr;
uint64   TCB::timeSliceCounter = 0;

bool  TCB::isFinished() const {
    return finished;
}

void TCB::setFinished(bool finished) {
    TCB::finished = finished;
}

 TCB * TCB::createThread(Body body) {
    return new  TCB(body,TIME_SLICE_SIZE);
}

void  TCB::yield() {
    __asm__ volatile ("ecall");
}

void  TCB::dispatch() {
     TCB *old = running;
    if (!old->isFinished()) {
        Scheduler::put(old);
    }
    running = Scheduler::get();
     TCB::contextSwitch(&old->context, &running->context);
}
uint64 TCB::getTimeSlice() const {

    return timeSlice;
}

void TCB::threadWrapper() {
    Riscv::popSppSpie();
    running->body();
    running->setFinished(true);
    TCB::yield();
}
