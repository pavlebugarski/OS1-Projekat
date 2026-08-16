//
// Created by os on 8/16/26.
//
#include "../h/handleSyscall.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.hpp"

void handleSyscall(uint64* context) {
    switch (context[10]) {
        case SYSCALL_MEM_ALLOC:
            MemoryAllocator::getInstance().alloc(context[11]*MEM_BLOCK_SIZE);
            break;
        case SYSCALL_MEM_FREE:
            MemoryAllocator::getInstance().free((void*)context[11]);
            break;
        default: context[10] = SYSCALL_UNKNOWN;
    }

}
