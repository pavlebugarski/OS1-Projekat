#ifndef MEMORY_ALLOCATOR_HPP
#define MEMORY_ALLOCATOR_HPP

#include "../lib/hw.h"

class MemoryAllocator {

    public:
    static MemoryAllocator& getInstance();
    void* alloc(size_t size);
    int free(void* ptr);


    private:
    struct FreeSegment {

        size_t size;
        FreeSegment* next;

    };
    MemoryAllocator();
    FreeSegment* freeListHead;
    MemoryAllocator(const MemoryAllocator&) = delete;//zabranjeno
    MemoryAllocator& operator=(const MemoryAllocator&) = delete;//zabranjeno
    static size_t roundUpBlock(size_t bytes);

};
#endif