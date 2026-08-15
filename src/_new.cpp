//
// Created by os on 8/15/26.
//
#include "../lib/mem.h"
void *operator new(uint64 n) {
    return __mem_alloc(n);
}
void *operator new[](uint64 n) {
    return __mem_alloc(n);
}
void operator delete(void *p)noexcept {
    __mem_free(p);
}
void operator delete[](void *p) {
    __mem_free(p);
}