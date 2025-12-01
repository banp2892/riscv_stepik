#pragma once

enum reg_t { A = 0, B = 1, C = 2, D = 3};

enum opcode_t { MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN = 0x30, OUT = 0x31 };

union operands_t{
    struct{
    enum reg_t rx, rs;
}regs;
enum reg_t reg;
int imm;

};

struct instr_t {
    union operands_t ops;
    enum opcode_t opc;
};

int encode (struct instr_t);

