#pragma once
#include <iostream>
#include <sys/mman.h>
#include <cstring>
#include <cstdint>
#include <vector>

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

enum Operation {
    ADD,
    SUB,
    MUL,
    DIV
};

typedef std::vector<uint8_t> instruction;
typedef double (*graph_jit_func)(double*);

void* allocate_executable_memory(size_t size, const uint8_t* code);

instruction emit_arithmetic_operation(Operation op, Register source, Register dest);
instruction emit_move_operation(Register source, Register dest);
instruction emit_move_placeholder_reg_operation(int placeholder_num, Register dest, uint8_t offset);
graph_jit_func make_function(std::vector<instruction> instructions);