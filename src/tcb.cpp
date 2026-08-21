//
// Created by os on 8/12/26.
//
#include "../h/tcb.hpp"

#include "../h/MemoryAllocator.hpp"
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

int TCB::exitCurrent() {
    if (running == nullptr) {
        return -1;
    }
    running->setFinished(true);
    dispatch();
    return 0;
}



TCB * TCB::createThread(Body body) {
    uint64* stack = nullptr;
    if (body != nullptr) {
        stack = (uint64*) MemoryAllocator::getInstance().alloc(STACK_SIZE*sizeof(uint64));
    }
    void* mem = MemoryAllocator::getInstance().alloc(sizeof(TCB));
    if (mem == nullptr) {
        return nullptr;
    }
    return ::new  (mem) TCB(body,TIME_SLICE_SIZE,stack);
}
TCB* TCB::createThread(Body body,uint64* stack) {
    if (body != nullptr && stack == nullptr) {
        return nullptr;
    }
    void* mem = MemoryAllocator::getInstance().alloc(sizeof(TCB));
    if (mem == nullptr) {
        return nullptr;
    }
    return ::new  (mem) TCB(body,TIME_SLICE_SIZE,stack);
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
    if (running->body != nullptr) {
        Riscv :: mc_sstatus(Riscv::SSTAUTS_SPP);
        Riscv::popSppSpie();
        running->body();
    }

    running->setFinished(true);
    TCB::yield();
}

void TCB::blockOn(List<TCB> &queue) {
    TCB *old = running;
    running =  Scheduler::get();
    if (running == nullptr) {
        return;
    }
    old->setStopped(true);
    queue.addLast(old);
    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::blockOff(List<TCB> &queue) {
    TCB *back = queue.removeFirst();
    if (back == nullptr) {
        return;
    }
    back->setStopped(false);
    Scheduler::put(back);
}
