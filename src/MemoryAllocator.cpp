#include "../h/MemoryAllocator.hpp"

MemoryAllocator& MemoryAllocator::getInstance() {
    static MemoryAllocator instance;
    return instance;

}
MemoryAllocator::MemoryAllocator() {
    freeListHead = (FreeSegment*) HEAP_START_ADDR;
    freeListHead->size =  HEAP_SIZE;
    freeListHead->next = nullptr;
}
size_t MemoryAllocator::roundUpBlock(size_t bytes) {

    return ((bytes + MEM_BLOCK_SIZE -1)/MEM_BLOCK_SIZE)*MEM_BLOCK_SIZE;

}
void* MemoryAllocator::alloc(size_t bytes) {
    if (bytes == 0) {
        return nullptr;
    }
    FreeSegment* freeSegment = freeListHead;
    FreeSegment* previous = nullptr;
    size_t total = roundUpBlock(bytes)+sizeof(FreeSegment);
    while (freeSegment != nullptr) {
        if(freeSegment->size >= total) {
            size_t rest = freeSegment->size - total;

            if(rest< sizeof(FreeSegment)+MEM_BLOCK_SIZE) {
                if (previous!=nullptr) {
                    previous->next = freeSegment->next;
                }else {
                    freeListHead = freeSegment->next;
                }
            }
            else {
                FreeSegment* temp = (FreeSegment*) ((char*) freeSegment+total);
                temp->size = rest;
                temp->next = freeSegment->next;
                if(previous!=nullptr) {
                    previous->next = temp;
                }
                else {
                    freeListHead = temp;
                }
                freeSegment->size = total;

            }
            return (void*)((char*)freeSegment+sizeof(FreeSegment));
        }
        previous = freeSegment;
        freeSegment = freeSegment->next;
    }
    return nullptr;
    }

int MemoryAllocator::free(void* ptr) {
    if (ptr == nullptr) {
        return -1;
    }
    FreeSegment* seg = (FreeSegment*)((char*)addr - sizeof(FreeSegment));
    FreeSegment* freeSegment = freeListHead;
    FreeSegment* previous = nullptr;

    while (freeSegment != nullptr&& freeSegment<seg) {
        previous = freeSegment;
        freeSegment = freeSegment->next;
    }
    seg->next = freeSegment;
    if (previous != nullptr) {
        previous->next = seg;

    }else {
        freeListHead = seg;
    }
    if (freeSegment != nullptr&&(char*)seg + seg->size == (char*)freeSegment) {
        seg->size += freeSegment->size;
        seg->next = freeSegment->next;
    }
    if (previous != nullptr&&previous->size+(char*)previous==(char*)seg) {
        previous->size += seg->size;
        previous->next  = seg->next;

    }
    return 0;


}
