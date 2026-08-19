#pragma once
#include "MemoryAllocator.hpp"

template<typename T>
class List {
private:
    struct Elem {
        T* data;
        Elem* next;
        Elem(T*data, Elem* next) : data(data), next(next) {}
    };
    Elem* head, * tail;

    static Elem* allocElem(T* data, Elem* next) {
        void* mem = MemoryAllocator::getInstance().alloc(sizeof(Elem));
        return ::new (mem) Elem(data, next);
    }
    static void freeElem(Elem* elem) {
        MemoryAllocator::getInstance().free(elem);
    }
public:
    List() : head(0), tail(0) {}
    List(const List<T> &) = delete;
    List<T> &operator=(const List<T> &) = delete;

    void addFirst(T* data) {
        Elem* elem = allocElem(data, head);
        head = elem;
        if (!tail) tail = head;
    }
    void addLast(T* data) {
        Elem* elem = allocElem(data, 0);
        if (!tail) {
            head = tail = elem;
        } else {
            tail->next = elem;
            tail = elem;
        }
    }
    T* removeFirst() {
        if (!head) return 0;
        Elem* elem = head;
        head = head->next;
        if (!head) tail = 0;
        T* ret = elem->data;
        freeElem(elem);
        return ret;
    }
    T* peekFirst() {
        if (!head) return 0;
        return head->data;
    }
    T* removeLast() {
        if (!head) return 0;
        Elem* prev = 0;
        for (Elem *el = head; el && el!=tail; el = el->next) {
            prev = el;
        }
        Elem* elem = tail;
        if (prev) prev->next = 0;
        else { head = 0; }
        tail = prev;
        T* ret = elem->data;
        freeElem(elem);
        return ret;
    }
    T* peekLast() {
        if (!tail) return 0;
        return tail->data;
    }
};