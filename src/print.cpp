//
// Created by os on 8/12/26.
//
#include "../h/print.hpp"
#include "../lib/console.h"
#include "../h/riscv.hpp"
void printString(char const * string) {
    uint64 sstatus = Riscv::r_sstatus();
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    while (*string!='\0') {
        __putc(*string);
        string++;
    }
    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);
}
void printInteger(uint64 number) {
    uint64 sstatus = Riscv::r_sstatus();
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    static char digits [] = "0123456789";
    char buf[16];
    int i,neg;
    uint x;
    neg = 0;
    if (number < 0) {
        neg = 1;
        x = -number;
    }
    else {
        x = number;
    }
    i = 0;
    do {
        buf[i++] = digits[x % 10];
    }while ((x /= 10) != 0);
    if (neg) buf[i++] = '-';
    while (--i >= 0) {
        __putc(buf[i]);
    }
    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);

}