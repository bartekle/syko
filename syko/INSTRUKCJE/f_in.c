#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_IN(void){
    DataType R1=getOpcode() & 0x000F;                       //identyfikacja numeru rejestru arg. 1
    DataType R2=(getOpcode() & 0x00F0)>>4;                  //identyfikacja numeru rejestru arg. 2

    printf("0x%04X[0x%04X]: IN R%d, R%d\n", getPC(), getOpcode(), R1, R2);

    //...
    //...
    //...

    setPC(getPC()+1);                                       //zwiêkszenie licznika rozkazów

    addCounter(1);
}
