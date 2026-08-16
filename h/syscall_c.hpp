#pragma once
#include "../lib/hw.h"
enum SyscallCode{
    SYSCALL_MEM_ALLOC = 0x01,
    SYSCALL_MEM_FREE = 0x02,
    SYSCALL_UNKNOWN = -1,
};
void* mem_alloc(size_t size);
int mem_free(void *ptr);
