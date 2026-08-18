//
// Created by os on 8/12/26.
//
#include "../h/print.hpp"
#include "../h/syscall_c.hpp"
void printString(char const * string) {

    while (*string!='\0') {
        putc(*string);
        string++;
    }

}
void printInteger(uint64 number) {

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
        putc(buf[i]);
    }

}