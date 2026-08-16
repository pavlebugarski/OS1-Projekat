#pragma once
#include "../lib/hw.h"
#include "../h/scheduler.hpp"
class TCB {
    public:
    using Body = void (*)();
    ~TCB() {
          delete stack;
    }



    static TCB* createThread(Body body);
    bool isFinished() const;
    void setFinished(bool finished);
    static void yield();
    uint64 getTimeSlice() const;
    static TCB* running;
private:
    explicit TCB(Body body,uint64 timeSlice):
        body(body), stack(body!=nullptr ? new uint64[STACK_SIZE] : nullptr),context({
            (uint64) &threadWrapper,
            stack!= nullptr ? (uint64)&stack[STACK_SIZE] : 0
        }),timeSlice(timeSlice),finished(false)
    {
         if (body != nullptr) {
             Scheduler::put(this);
         }

    }
    struct Context {
        uint64 ra;
        uint64 sp;

    };
    static void contextSwitch(Context *oldContext, Context *runningContext);
    Body body;
    uint64 *stack;
    Context context;
    uint64 timeSlice;
    bool finished;
    friend class Riscv;
    static void threadWrapper();
    static uint64 timeSliceCounter;
    static void dispatch();
    static uint64 constexpr STACK_SIZE = 1024;
    static uint64 constexpr TIME_SLICE_SIZE = 2;
};
