//
// Created by os on 8/21/26.
//
#include "../h/semaphore.hpp"
#include "../h/tcb.hpp"

void semaphore::wait() {
    value--;
    if (value<0) {
        TCB::blockOn(blockedQueue);
    }

}
void semaphore::signal() {
    value++;
    if (value<=0) {
        TCB::blockOff(blockedQueue);
    }
}
semaphore::semaphore(const int value) {
    if (value <0) {
        this->value = 0;
    }else {
        this->value = value;
    }
}
