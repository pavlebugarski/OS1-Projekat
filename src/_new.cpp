//
// Created by os on 8/15/26.
//
#include "../h/syscall_c.hpp"
void *operator new(uint64 n) {
    return mem_alloc((size_t)n);
}
void *operator new[](uint64 n) {
    return mem_alloc((size_t)n);
}
void operator delete(void *p)noexcept {
    mem_free(p);
}
void operator delete[](void *p) {
    mem_free(p);
}