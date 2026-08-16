#pragma once
#include "../lib/hw.h"
enum SyscallCode{
    SYSCALL_MEM_ALLOC = 0x01,
    SYSCALL_MEM_FREE = 0x02,
    SYSCALL_THREAD_CREATE = 0x11,
    SYSCALL_THREAD_EXIT = 0x12,
    SYSCALL_THREAD_DISPATCH = 0x13,
    SYSCALL_UNKNOWN = -1,
};
void* mem_alloc(size_t size);
int mem_free(void *ptr);
