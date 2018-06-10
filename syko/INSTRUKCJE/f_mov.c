#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
void F_MOV(void){
DataType R=getOpcode() & 0x000F;
const int c 124;
printf("0x%04X[0x%04X]: MOV R%d, %d\n", getPC(), getOpcode(),R,c);
GEN_REG[R]=c;
setPC(getPC()+1);
addCounter(1);
}
