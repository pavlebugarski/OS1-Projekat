//
// Created by os on 8/17/26.
//
#include "../h/syscall_c.hpp"
#include "../h/doSyscall.hpp"
int thread_exit() {
    uint64 result;
    result = doSyscall(SYSCALL_THREAD_EXIT);
    return (int)result;
}
int thread_create(thread_t *handle,
    void(*start_routine)(void *),
    void *arg) {
    void* stackSpace = mem_alloc(DEFAULT_STACK_SIZE);
    if (stackSpace == nullptr) {
        return -1;
    }
    uint64 result = doSyscall(
        SYSCALL_THREAD_CREATE,
        (uint64) start_routine,
        (uint64)stackSpace);
    if (result == 0) {
        return -1;
    }
    *handle = (thread_t ) result;
    return 0;
}
void thread_dispatch() {
    doSyscall(SYSCALL_THREAD_DISPATCH);
}