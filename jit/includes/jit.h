#pragma once

#include <sys/mman.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>

typedef std::vector<uint8_t> instruction;
typedef double (*graph_jit_func)(double*);

enum Operation {
    ADD, SUB, MUL, DIV
};

enum Register64 {
    RAX, RCX, RDX, RBX, RSP, RBP, RSI, RDI,
    R8, R9, R10, R11, R12, R13, R14, R15,
};

enum SIMDRegister {
    XMM0, XMM1, XMM2, XMM3,
    XMM4, XMM5, XMM6, XMM7
};


std::vector<uint8_t> read_literal_bytes(uint64_t literal);

instruction emit_mov_literal(Register64 dest, uint64_t literal);
instruction emit_mov_double_literal(SIMDRegister dest, Register64 src);
instruction emit_mov_double_literal(SIMDRegister dest, double literal);
instruction emit_mov(Register64 dest, Register64 src);
instruction emit_mov_simd(SIMDRegister dest, Register64 src);