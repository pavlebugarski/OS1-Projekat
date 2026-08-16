//
// Created by os on 8/12/26.
//
#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/scheduler.hpp"
#include "../h/syscall_c.hpp"

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
    register uint64 x10 __asm__ ("x10") = SYSCALL_THREAD_DISPATCH;
    __asm__ volatile("ecall" : "+r"(x10) : :  "memory");
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
