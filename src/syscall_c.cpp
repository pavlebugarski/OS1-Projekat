//
// Created by os on 8/15/26.
//
#include "../h/doSyscall.hpp"
#include "../h/syscall_c.hpp"

void* mem_alloc(size_t size) {
    size_t blocks = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
    uint64 result = doSyscall(SYSCALL_MEM_ALLOC, blocks);
    return (void*) result;
}

int mem_free(void *ptr) {
    uint64 result = doSyscall(SYSCALL_MEM_FREE, (uint64) ptr);
    return (int) result;
}
