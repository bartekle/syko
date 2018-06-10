#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_CLI(void){
MEMD[SREG]=MEMD[SREG] & (~(1<<7));
printf("0x%04X[0x%04X]: SBI",getPC(),getOpcode());
setPC(getPC()+1);
addCounter(1);
}
