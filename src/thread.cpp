//
// Created by os on 8/17/26.
//
#include "../h/thread.hpp"
// src/syscall_cpp.cpp

Thread::Thread() : myHandle(nullptr), body(nullptr), bodyArg(nullptr) {}

Thread::Thread(void (*body)(void*), void* arg) : myHandle(nullptr), body(body), bodyArg(arg) {}

Thread::~Thread() = default;

void Thread::run() {
    // podrazumevano prazno telo - podklase ga redefinisu ako ne koriste
    // konstruktor sa pokazivacem na funkciju
}

void Thread::wrapper(void* arg) {
    Thread* self = (Thread*) arg;
    if (self->body != nullptr) {
        self->body(self->bodyArg);
    } else {
        self->run();
    }
}

int Thread::start() {
    return thread_create(&myHandle, wrapper, this);
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::exit() {
    return thread_exit();
}