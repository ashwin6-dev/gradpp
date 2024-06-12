#include "includes/jit.h"

void* allocate_executable_memory(size_t size, const uint8_t* code) 
{
    void* mem = mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        return nullptr;
    }
    std::memcpy(mem, code, size);
    return mem;
}

instruction emit_arithmetic_operation(Operation op, Register source, Register dest) 
{
    uint8_t prefix = 0xf2;
    uint8_t opcode_prefix = 0x0f;
    uint8_t opcode;
    uint8_t operands = (dest << 3) | source;
    uint8_t mod = 3 << 6;
    
    if (op == ADD) {
        opcode = 0x58;
    }else if (op == SUB) {
        opcode = 0x5c;
    }else if (op == MUL) {
        opcode = 0x59;
    }else if (op == DIV) {
        opcode = 0x5e;
    }

    std::vector<uint8_t> code { 
        prefix,
        opcode_prefix,
        opcode,
        static_cast<uint8_t>(mod | operands),
    };

    return code;
}

instruction emit_move_operation(Register source, Register dest)
{
    uint8_t prefix = 0xf2;
    uint8_t opcode_prefix = 0x0f;
    uint8_t opcode = 0x10;
    uint8_t operands = (dest << 3) | source;
    uint8_t mod = 3 << 6;

    std::vector<uint8_t> code { 
        prefix,
        opcode_prefix,
        opcode,
        static_cast<uint8_t>(mod | operands),
    };

    return code;
}

graph_jit_func make_function(std::vector<instruction> instructions)
{
    uint8_t* code = (uint8_t*) calloc(instructions.size(), 8);
    int code_index = 0;

    for (instruction ins : instructions) {
        for (uint8_t byte : ins) {
            code[code_index++] = byte;
        }
    }

    code[code_index++] = 0xc3;

    void* mem = allocate_executable_memory(code_index, code);
    graph_jit_func func = reinterpret_cast<graph_jit_func>(mem);

    return func;
}

int main() {
    // Cast the memory to a function pointer and call it
    graph_jit_func add_func = make_function(
        std::vector<instruction> { 
            emit_arithmetic_operation(MUL, XMM1, XMM0),
            emit_move_operation(XMM0, XMM2),
            emit_arithmetic_operation(ADD, XMM1, XMM2),
            emit_move_operation(XMM2, XMM0)
        }
    );

    // Call the JIT-compiled function with two float arguments
    double result = add_func(2.0, 2.012937421);
    std::cout << "Result: " << result << std::endl;

    // Free the executable memory

    return 0;
}
