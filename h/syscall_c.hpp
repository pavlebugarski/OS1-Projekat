#pragma once
#include "../lib/hw.h"
enum SyscallCode{
    SYSCALL_MEM_ALLOC = 0x01,
    SYSCALL_MEM_FREE = 0x02,
    SYSCALL_THREAD_CREATE = 0x11,
    SYSCALL_THREAD_EXIT = 0x12,
    SYSCALL_THREAD_DISPATCH = 0x13,
    SYSCALL_PUTC = 0x42,
    SYSCALL_UNKNOWN = -1,
};

class _thread;
typedef _thread *thread_t;
void* mem_alloc(size_t size);
int mem_free(void *ptr);
int thread_exit();
int thread_create(
    thread_t *handle,
    void(*start_routine)(void *),
    void *arg
    );
void thread_dispatch();
void putc(char c);