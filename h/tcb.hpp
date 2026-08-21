#pragma once
#include "../lib/hw.h"
#include "../h/scheduler.hpp"
class TCB {
    public:

    using Body = void (*)();
    ~TCB() {
          delete stack;
    }


    static void blockOn(List<TCB>& queue);
    static void blockOff(List<TCB>& queue);
    static TCB* createThread(Body body);
    static TCB* createThread(Body body,uint64* stack);
    bool isFinished() const;
    void setFinished(bool finished);
    static void yield();
    uint64 getTimeSlice() const;
    static int exitCurrent();
    static TCB* running;
private:
    explicit TCB(Body body,uint64 timeSlice, uint64* stack):
                                body(body),
                                stack(body!=nullptr ? stack : nullptr),
                                context({
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
    bool stopped = false;

public:
    bool IsStopped() const {
        return stopped;
    }
    void setStopped(bool stopped) {
        this->stopped = stopped;
    }

private:
    friend class Riscv;
    static void threadWrapper();
    static uint64 timeSliceCounter;
    static void dispatch();
    static uint64 constexpr STACK_SIZE = 1024;
    static uint64 constexpr TIME_SLICE_SIZE = 2;
};
