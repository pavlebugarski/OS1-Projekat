//
// Created by os on 8/18/26.
//
#include "../h/syscall_c.hpp"
#include "../h/doSyscall.hpp"

void putc(char c) {
    doSyscall(SYSCALL_PUTC, (uint64) c);
}