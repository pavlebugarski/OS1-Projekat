//
// Created by os on 8/15/26.
//
#include "../h/syscall_c.hpp"

static uint64 doSyscall(uint64 code, uint64 agr1= 0,uint64 agr2= 0,uint64 agr3= 0) {
    register uint64 a0 __asm__ ("x10") = code;
    register uint64 a1 __asm__ ("x11") = agr1;
    register uint64 a2 __asm__ ("x12") = agr2;
    register uint64 a3 __asm__ ("x13") = agr3;
    __asm__ volatile ("ecall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a3) : "memory");
    return a0;
}

void* mem_alloc(size_t size) {
    size_t blocks = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
    uint64 result = doSyscall(SYSCALL_MEM_ALLOC, blocks);
    return (void*) result;
}

int mem_free(void *ptr) {
    uint64 result = doSyscall(SYSCALL_MEM_FREE, (uint64) ptr);
    return (int) result;
}
