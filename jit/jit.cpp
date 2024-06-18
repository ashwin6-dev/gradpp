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

graph_jit_func make_function(std::vector<instruction> instructions)
{
    int total_size = 0;
    for (instruction ins : instructions) {
        total_size += ins.size();
    }
    total_size++;

    uint8_t* code = (uint8_t*) calloc(total_size, 1);
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

/*
Reads in 64-bit literal and returns it in LITTLE ENDIAN
*/
std::vector<uint8_t> read_literal_bytes(uint64_t literal)
{
    uint8_t last_byte = 0xff;
    std::vector<uint8_t> bytes;

    for (int i = 0; i < 8; i++) {
        uint8_t byte = static_cast<uint8_t>(last_byte & literal);
        bytes.push_back(byte);
        literal >>= 8;
    }

    return bytes;
}

instruction emit_mov_literal(Register64 dest, uint64_t literal)
{
    uint8_t rex_prefix = 0x48;
    uint8_t opcode = static_cast<uint8_t>(0xb8 + dest); // opcode for mov is 0xb8 + dest register encoding for literals
    std::vector<uint8_t> literal_bytes = read_literal_bytes(literal);

    std::vector<uint8_t> instruction {
        rex_prefix,
        opcode
    };

    instruction.insert(instruction.end(), literal_bytes.begin(), literal_bytes.end());
    return instruction;
}

instruction emit_mov_double_literal(SIMDRegister dest, double literal)
{
    uint64_t double_bits;
    std::memcpy(&double_bits, &literal, sizeof(uint64_t));

    std::vector<uint8_t> first_instruction = emit_mov_literal(RAX, double_bits);
    std::vector<uint8_t> second_instruction = emit_mov_simd(dest, RAX);

    first_instruction.insert(first_instruction.end(), second_instruction.begin(), second_instruction.end());
    return first_instruction;
}

instruction emit_mov_simd(SIMDRegister dest, Register64 src)
{
    uint8_t sse = 0x66;
    uint8_t rex_prefix = 0x48;
    uint8_t opcode_prefix = 0x0f;
    uint8_t opcode = 0x6e;
    uint8_t mod = 0xc0 | (dest << 3) | src;

    std::vector<uint8_t> instruction {
        sse,
        rex_prefix,
        opcode_prefix,
        opcode,
        mod
    };

    return instruction;
}

instruction emit_mov(Register64 dest, Register64 src)
{
    uint8_t rex_prefix = 0x48;
    uint8_t opcode = 0x8b;
    uint8_t mod = 0xc0 | (dest << 3) | src;

    std::vector<uint8_t> instruction {
        rex_prefix,
        opcode,
        mod
    };

    return instruction;
}

instruction emit_arithmetic_operation(Operation op, SIMDRegister dest, SIMDRegister src) 
{
    uint8_t prefix = 0xf2;
    uint8_t opcode_prefix = 0x0f;
    uint8_t opcode;
    uint8_t mod = 0xc0 | dest << 3 | src;
    
    if (op == ADD) {
        opcode = 0x58;
    }else if (op == SUB) {
        opcode = 0x5c;
    }else if (op == MUL) {
        opcode = 0x59;
    }else if (op == DIV) {
        opcode = 0x5e;
    }

    std::vector<uint8_t> instruction { 
        prefix,
        opcode_prefix,
        opcode,
        mod
    };

    return instruction;
}

int main()
{
    std::vector<instruction> instructions {
        emit_mov_double_literal(XMM1, 1.5),
        emit_mov_double_literal(XMM0, 2.1),
        emit_arithmetic_operation(ADD, XMM0, XMM1)
    };

    graph_jit_func func = make_function(instructions);

    double inputs[1];
    inputs[0] = 1.0;

    double res = func(inputs);
    
    std::cout <<  "result: " << res << std::endl;
}