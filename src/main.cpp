#include "../lib/console.h"
#include "../h/workers.hpp"
#include "../h/print.hpp"
#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../h/syscall_c.hpp"
/*int main() {
    TCB * threads[5];
    threads[0] = TCB::createThread(nullptr);
    TCB::running = threads[0];
    threads[1] = TCB::createThread(workerBodyA);
    printString("ThreadA created\n");
    threads[2] = TCB::createThread(workerBodyB);
    printString("ThreadB created\n");
    threads[3] = TCB::createThread(workerBodyC);
    printString("ThreadC created\n");
    threads[4] = TCB::createThread(workerBodyD);
    printString("ThreadD created\n");
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    while (!(threads[1]->isFinished() &&
            threads[2]->isFinished() &&
            threads[3]->isFinished() &&
            threads[4]->isFinished())) {
        TCB::yield();
    }
    for (auto &corutine: threads) {
        delete corutine;
    }
    printString("finished\n");
    return 0;
}*/
void userMain(void*arg) {
    printString("Test mem_alloc/mem_free: pocetak\n");
    void* testPtr = mem_alloc(100);
    if (testPtr == nullptr) {
        printString("mem_alloc: FAIL (vratio nullptr)\n");
    } else {
        printString("mem_alloc: OK, pokazivac dobijen\n");

        *((uint64*) testPtr) = 12345;
        uint64 readBack = *((uint64*) testPtr);
        if (readBack == 12345) {
            printString("Upis/citanje u alocirani prostor: OK\n");
        } else {
            printString("Upis/citanje u alocirani prostor: FAIL\n");
        }

        int freeResult = mem_free(testPtr);
        if (freeResult == 0) {
            printString("mem_free: OK\n");
        } else {
            printString("mem_free: FAIL, kod greske=");
            printInteger(freeResult);
            printString("\n");
        }
    }

    printString("Test mem_alloc/mem_free: kraj\n");
    thread_t threads[4];
    thread_create(&threads[0], workerBodyA, nullptr);
    thread_create(&threads[1], workerBodyB, nullptr);
    thread_create(&threads[2], workerBodyC, nullptr);
    thread_create(&threads[3], workerBodyD, nullptr);
    for (auto &t : threads) {
        while (!((TCB*) t)->isFinished()) {
            thread_dispatch();
        }
    }

    printString("userMain zavrsen\n");

}
int main() {
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);

    // "glavna" koroutina - predstavlja sam main() kao nit bez tela
    TCB* mainThread = TCB::createThread(nullptr);
    TCB::running = mainThread;

    // jedina nit koju jezgro pravi direktno - kroz pravi sistemski poziv,
    // ne kroz TCB::createThread
    thread_t userThread;
    if (thread_create(&userThread, userMain, nullptr) != 0) {
        printString("greska: userMain se ne moze pokrenuti\n");
        return -1;
    }

    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);

    while (!((TCB*) userThread)->isFinished()) {
        TCB::yield();
    }

    delete mainThread;
    printString("finished\n");
    return 0;
}
