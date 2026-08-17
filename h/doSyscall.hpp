#pragma once
#include "../lib/hw.h"

uint64 doSyscall(uint64 code, uint64 arg1 = 0, uint64 arg2 = 0, uint64 arg3 = 0);