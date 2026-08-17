//
// Created by os on 8/17/26.
//
#include "../h/doSyscall.hpp"

uint64 doSyscall(uint64 code, uint64 arg1, uint64 arg2, uint64 arg3) {
    register uint64 a0 __asm__ ("x10") = code;
    register uint64 a1 __asm__ ("x11") = arg1;
    register uint64 a2 __asm__ ("x12") = arg2;
    register uint64 a3 __asm__ ("x13") = arg3;
    __asm__ volatile ("ecall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a3) : "memory");
    return a0;
}