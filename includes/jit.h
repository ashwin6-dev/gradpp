#pragma once
#include <iostream>
#include <sys/mman.h>
#include <cstring>
#include <cstdint>
#include <vector>

#include "graph.h"
#include "register-allocator.h"
#include "ops.h"
#include "const.h"
#include "register.h"

typedef std::vector<uint8_t> instruction;
typedef double (*graph_jit_func)(double*);

enum Operation {
    ADD,
    SUB,
    MUL,
    DIV
};

class JITVisitor {
public:
    std::vector<instruction> visit(Node* node, register_allocation allocation);
    std::vector<instruction> visit(Placeholder* node, register_allocation allocation);
    std::vector<instruction> visit(Const* node, register_allocation allocation);
    std::vector<instruction> visit(Add* node, register_allocation allocation);
    std::vector<instruction> visit(Sub* node, register_allocation allocation);
    std::vector<instruction> visit(Mul* node, register_allocation allocation);
};

void* allocate_executable_memory(size_t size, const uint8_t* code);

instruction emit_arithmetic_operation(Operation op, Register source, Register dest);
instruction emit_move_operation(Register source, Register dest);
instruction emit_move_placeholder_reg_operation(int placeholder_num, Register dest);
graph_jit_func make_function(std::vector<instruction> instructions);

graph_jit_func jit_graph(Graph graph);