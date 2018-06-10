#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_NOP(void){
    printf("0x%04X[0x%04X]: No operation!\n", getPC(), getOpcode());
    addCounter(1);
}
