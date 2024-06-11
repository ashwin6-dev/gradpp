#include "includes/jit.h"

void* allocate_executable_memory(size_t size, const uint8_t* code) {
    void* mem = mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        return nullptr;
    }
    std::memcpy(mem, code, size);
    return mem;
}

uint8_t* add_doubles(Register source, Register dest)
{
    uint8_t prefix = 0xf2;
    uint8_t opcode_prefix = 0x0f;
    uint8_t opcode = 0x58;
    uint8_t operands = (dest << 3) | source;
    uint8_t mod = 3 << 6;

    uint8_t* code = (uint8_t*) calloc(5, sizeof(uint8_t));
    if (!code) {
        return nullptr; // Handle allocation failure
    }

    code[0] = prefix;
    code[1] = opcode_prefix;
    code[2] = opcode;
    code[3] = mod | operands;
    code[4] = 0xc3;

    return code;
}

uint8_t* sub_doubles(Register source, Register dest)
{
    uint8_t prefix = 0xf2;
    uint8_t opcode_prefix = 0x0f;
    uint8_t opcode = 0x5c;
    uint8_t operands = (dest << 3) | source;
    uint8_t mod = 3 << 6;

    uint8_t* code = (uint8_t*) calloc(5, sizeof(uint8_t));
    if (!code) {
        return nullptr; // Handle allocation failure
    }

    code[0] = prefix;
    code[1] = opcode_prefix;
    code[2] = opcode;
    code[3] = mod | operands;
    code[4] = 0xc3;

    return code;
}

int main() {
    uint8_t* code = sub_doubles(XMM1, XMM0);

    if (!code) {
        return 1; // Handle allocation failure
    }

    // Allocate executable memory and copy the code into it
    size_t code_size = sizeof(&code);
    std::cout << (int) code_size << std::endl;

    for (int i = 0; i < code_size; i++) {
        printf("%x\n", code[i]);
    }

    void* mem = allocate_executable_memory(code_size, code);
    delete[] code; // Free dynamically allocated memory after use

    if (!mem) {
        return 1; // Handle memory allocation failure
    }

    // Cast the memory to a function pointer and call it
    typedef double (*func_t)(double, double);
    func_t add_func = reinterpret_cast<func_t>(mem);

    // Call the JIT-compiled function with two float arguments
    double result = add_func(1.513, 3.0);
    std::cout << "Result: " << result << std::endl;

    // Free the executable memory
    munmap(mem, code_size);

    return 0;
}
