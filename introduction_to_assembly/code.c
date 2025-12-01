#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

enum reg_t {A = 00, B = 01, C = 2, D = 3};
enum opcode_t {MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN =0x30, OUT = 0x31};

union operands_t {
    struct{
	enum reg_t rx, rs;
    } regs;
    enum reg_t reg;
    int imm;
};

struct instr_t {
    union operands_t ops;
    enum opcode_t opc;
};

int encode(struct instr_t instr){
    int encoded;
    switch(instr.opc){
	case MOVI:
	    encoded =(instr.ops.imm & 0x7F);
	    break;
	case ADD:
	    encoded = (instr.opc << 4) | (instr.ops.regs.rx<<2) | (instr.ops.regs.rs);
	    break;
	case SUB:
	    encoded = (instr.opc << 4) | (instr.ops.regs.rx<<2) | (instr.ops.regs.rs);
	    break;
	case MUL:
	    encoded = (instr.opc << 4) | (instr.ops.regs.rx<<2) | (instr.ops.regs.rs);
	    break;
	case DIV:
	    encoded = (instr.opc << 4) | (instr.ops.regs.rx<<2) | (instr.ops.regs.rs);
	    break;
	case IN:
	    encoded = (instr.opc << 2) | (instr.ops.reg);
	    break;
	case OUT:
	    encoded = (instr.opc << 2) | (instr.ops.reg);
	    break;
	default:
	    fprintf(stderr, "Unknwn opcode\n");
	    abort();
}
    return encoded;
}


static enum reg_t parse_reg(char simvol){
    switch(simvol){
	case 'A' : return A;
	case 'B' : return B;
	case 'C' : return C;
	case 'D' : return D;
	default:{
	    printf("ERROR");
	    exit(0);
	}

}

}

int parse_out(){
    int reg, res;
    struct instr_t instr;
    char sreg;
    res = scanf("%s", &sreg);
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    reg = parse_reg(sreg);
    instr.opc = OUT;
    instr.ops.reg = reg;
    return encode(instr);
}

int parse_in(){
    int reg, res;
    struct instr_t instr;
    char sreg;
    res = scanf("%s", &sreg);
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    reg = parse_reg(sreg);
    instr.opc = IN;
    instr.ops.reg = reg;
    return encode(instr);
}

int parse_movi(){
    int imm, res;
    struct instr_t instr;
    res = scanf("%d", &imm);
    if (res != 1 || imm > (1 << 7)){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    instr.opc = MOVI;
    instr.ops.imm = imm;
    return encode(instr);
}


int parse_div(){
    int res;
    int rx, rs;
    struct instr_t instr;
    char crx, crs;
    res = scanf("%s", &crx);
    if (res != 1){
	fprintf(stderr, "ERROR\n");
    }
    rx = parse_reg(crx);
    res = scanf("%s", &crs);
    res = (crs==',') ? (scanf("%s", &crs)) : res;
    if (res != 1 || rs < (1<<7)){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rs = parse_reg(crs);
    instr.opc = DIV;
    instr.ops.regs.rx = rx;
    instr.ops.regs.rs = rs;
    return encode(instr);
}

int parse_mul(){
    int res;
    int rx, rs;
    struct instr_t instr;
    char crx, crs;
    res = scanf("%s", &crx);
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rx = parse_reg(crx);
    res = scanf("%s", &crs);
    res = (crs==',') ? (scanf("%s", &crs)) : res;
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rs = parse_reg(crs);
    instr.opc = MUL;
    instr.ops.regs.rx = rx;
    instr.ops.regs.rs = rs;
    return encode(instr);
}

int parse_sub(){
    int res;
    int rx, rs;
    struct instr_t instr;
    char crx, crs;
    res = scanf("%s", &crx);
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rx = parse_reg(crx);
    res = scanf("%s", &crs);
    res = (crs==',') ? (scanf("%s", &crs)) : res;
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rs = parse_reg(crs);
    instr.opc = SUB;
    instr.ops.regs.rx = rx;
    instr.ops.regs.rs = rs;
    return encode(instr);
}

int parse_add(){
    int res;
    int rx, rs;
    struct instr_t instr;
    char crx, crs;
    res = scanf("%s", &crx);
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rx = parse_reg(crx);
    res = scanf("%s", &crs);
    res = (crs==',') ? (scanf("%s", &crs)) : res;
    if (res != 1){
	fprintf(stderr, "ERROR\n");
	abort();
    }
    rs = parse_reg(crs);
    instr.opc = ADD;
    instr.ops.regs.rx = rx;
    instr.ops.regs.rs = rs;
    return encode(instr);
}





int main(){
    char buf[16];
    while(scanf("%15s", buf) ==1){
	int encoded;
	if (strcmp(buf,"MOVI") == 0)
	    encoded = parse_movi();
	else if (strcmp(buf,"ADD") == 0)
	    encoded = parse_add();
	else if (strcmp(buf,"SUB") == 0)
	    encoded = parse_sub();
	else if (strcmp(buf,"MUL") == 0)
	    encoded = parse_mul();
	else if (strcmp(buf,"DIV") == 0)
	    encoded = parse_div();
	else if (strcmp(buf,"IN") == 0)
	    encoded = parse_in();
	else if (strcmp(buf,"OUT") == 0)
	    encoded = parse_out();
	else{
	    fprintf(stderr,"ERROR <%s> \n", buf);
	    abort();
	    }
	printf("0x%x ", encoded);
	fflush(stdout);
    }
printf("\n");

}

