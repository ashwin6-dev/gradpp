#pragma once
#include <iostream>
#include <sys/mman.h>
#include <cstring>
#include <cstdint>

enum Register {
    XMM0,
    XMM1,
    XMM2,
    XMM3,
    XMM4,
    XMM5,
    XMM6,
    XMM7
};

void* allocate_executable_memory(size_t size, const uint8_t* code);
uint8_t* add_doubles(Register source, Register dest);
uint8_t* sub_doubles(Register source, Register dest);