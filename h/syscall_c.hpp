#pragma once
#include "../lib/hw.h"
enum SyscallCode{
    SYSCALL_MEM_ALLOC = 0x01,
    SYSCALL_MEM_FREE = 0x02,
    SYSCALL_THREAD_CREATE = 0x11,
    SYSCALL_THREAD_EXIT = 0x12,
    SYSCALL_THREAD_DISPATCH = 0x13,
    SYSCALL_SEM_OPEN = 0x21,
    SYSCALL_SEM_CLOSE = 0x22,
    SYSCALL_SEM_WAIT = 0x23,
    SYSCALL_SEM_SIGNAL = 0x24,
    SYSCALL_SEM_WAIT_N = 0x25,
    SYSCALL_SEM_SIGNAL_N = 0x26,
    SYSCALL_PUTC = 0x42,
    SYSCALL_UNKNOWN = -1,

};

class _thread;
typedef _thread *thread_t;
class _sem;
typedef _sem *sem_t;
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
int sem_open(sem_t* handle, unsigned init);
int sem_close(sem_t handle);
int sem_wait(sem_t id);
int sem_signal(sem_t id);
int sem_wait_n(sem_t id, unsigned n);
int sem_signal_n(sem_t id, unsigned n);