//
// Created by os on 8/13/26.
//
#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/tcb.hpp"
#include "../h/handleSyscall.hpp"
#include "../h/syscall_c.hpp"

void Riscv::handleSupervisorTrap(uint64* context) {

    uint64 scause = r_scause();
    if (scause == 0x0000000000000009UL) {
        //sinhrona promena konteksta
        //sepc je kao pc program counter
        uint64 code = context[10];
        if (code == SYSCALL_THREAD_DISPATCH) {
            uint64 sepc = r_sepc()+4;
            uint64 sstatus = r_sstatus();
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }else {
            handleSyscall(context);
            w_sepc(r_sepc()+4);
        }
    }else if (scause == 0x8000000000000001UL) {
        //asinhrona promena konteksta
        //obrada timera
        TCB::timeSliceCounter++;
        if (TCB::timeSliceCounter >= TCB::running->getTimeSlice()) {
            uint64 sepc = r_sepc();
            uint64 sstatus = r_sstatus();
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }
        mc_sip(SIP_SSIP);


    }else if (scause == 0x8000000000000009UL) {
        //konzola
        console_handler();
    }else {
        //ostalo
    }
}

void Riscv::popSppSpie() {
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile ("sret");
}
