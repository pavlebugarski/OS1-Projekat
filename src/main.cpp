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
int main() {
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);

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
}
