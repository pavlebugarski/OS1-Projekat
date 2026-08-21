//
// Created by os on 8/16/26.
//
#include "../h/handleSyscall.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.hpp"
#include "../h/tcb.hpp"
#include "../lib/console.h"
void handleSyscall(uint64* context) {
    uint64 result;
    switch (context[10]) {
        case SYSCALL_MEM_ALLOC:
            result = (uint64) MemoryAllocator::getInstance().alloc(context[11]*MEM_BLOCK_SIZE);
            break;
        case SYSCALL_MEM_FREE:
            result = (uint64) MemoryAllocator::getInstance().free((void*)context[11]);
            break;
        case SYSCALL_THREAD_CREATE:
            result = (uint64) TCB::createThread((TCB::Body)context[11],(uint64*) context[12]);
            break;
        case SYSCALL_THREAD_EXIT:
            result = (uint64) TCB::exitCurrent();
            break;
        case SYSCALL_PUTC:
            __putc((char) context[11]);
            result = 0;
            break;

        default: result = (uint64) SYSCALL_UNKNOWN;
    }
    context[10] = result;

}
