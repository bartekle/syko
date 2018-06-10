#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_JMP_REL(void){
    printf("0x%04X[0x%04X]: JMP PC+0x%04X\n", getPC(), getOpcode(), getOpcode() & 0x0FFF);

    if((getOpcode() & 0x0800)==0)
        setPC(getPC()+(getOpcode() & 0x0FFF));
    else
        setPC(getPC()-(0x1000-(getOpcode() & 0x0FFF)));

    addCounter(1);
}
