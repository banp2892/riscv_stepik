#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

enum reg_t {A = 00, B = 01, C = 2, D = 3};
enum opcode_t {MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN =0x30, OUT = 0x31};

union operands_t {
    struct{
	enum reg_t rx, rs;
    } regs;
    enum reg_t reg;
    int imm;
};

typedef struct instr_t {
    union operands_t ops;
    enum opcode_t opc;
}instr_t;





struct instr_t encode(uint16_t vhod){
struct instr_t res;
if(vhod >> 7 == 0){ // MOVI
    res.opc = MOVI;
    res.ops.imm = vhod&127;
    return res;
}
else if(vhod >> 4 == 8){ // ADD
    res.opc = ADD;
    res.ops.regs.rx = (vhod & 12)>>2;
    res.ops.regs.rs = vhod & 3;
    return res;
}
else if(vhod >>4 == 9){ // sub
    res.opc = SUB;
    res.ops.regs.rx = (vhod & 12)>>2;
    res.ops.regs.rs = vhod & 3;
    return res;
}
else if(vhod >>4 == 10){ // MUL
    res.opc = MUL;
    res.ops.regs.rx = (vhod & 12)>>2;
    res.ops.regs.rs = vhod & 3;
    return res;
}
else if(vhod >>4 == 11){ // DIV
    res.opc = DIV;
    res.ops.regs.rx = (vhod & 12)>>2;
    res.ops.regs.rs = vhod & 3;
    return res;
}
else if (vhod >>2 == 0x30) { //IN
    res.opc = IN;
    res.ops.reg = vhod & 3;
    return res;
}
else if(vhod >>2 ==0x31){ //OUT
    res.opc = OUT;
    res.ops.reg = vhod & 3;
    return res;
}

else{
    fprintf(stderr, "ERROR\n");
    fflush(stderr);
    exit(0);
}

}

char encode_simvol(int vhod){
if(vhod == A){
return 'A';
}
else if(vhod == B){
return 'B';
}
else if(vhod == C){
return 'C';
}
else if(vhod == D){
return 'D';
}
else{
fprintf(stderr,"ERROR\n");
fflush(stderr);
exit(0);
}

}


char* pechat(instr_t vhod){
    char* buf;
    buf = (char*)malloc(32*sizeof(char));
    if(vhod.opc == MOVI){
	sprintf(buf, "MOVI %d", vhod.ops.imm);
	return buf;
    }
    else if(vhod.opc == ADD){
	sprintf(buf, "ADD %c, %c", encode_simvol(vhod.ops.regs.rx),encode_simvol(vhod.ops.regs.rs));
	return buf;
}
    else if(vhod.opc == SUB){
	sprintf(buf, "SUB %c, %c", encode_simvol(vhod.ops.regs.rx),encode_simvol(vhod.ops.regs.rs));
	return buf;
}
    else if(vhod.opc == DIV){
	sprintf(buf, "DIV %c, %c", encode_simvol(vhod.ops.regs.rx),encode_simvol(vhod.ops.regs.rs));
	return buf;
}
    else if(vhod.opc == MUL){
	sprintf(buf, "MUL %c, %c", encode_simvol(vhod.ops.regs.rx),encode_simvol(vhod.ops.regs.rs));
	return buf;
}
    else if(vhod.opc == IN){
	sprintf(buf, "IN %c", encode_simvol(vhod.ops.reg));
	return buf;
}
    else if(vhod.opc == OUT){
	sprintf(buf, "OUT %c", encode_simvol(vhod.ops.reg));
	return buf;
}
    else{
    fprintf(stderr, "ERROR\n");
    fflush(stderr);
    exit(0);
}
}


int main(){

    uint16_t vhod;
    while(scanf("%hx", &vhod) ==1){
	struct instr_t vernulo = encode(vhod);
	fprintf(stdout, "%s\n", pechat(vernulo));
	fflush(stdout);
	


    }

}

