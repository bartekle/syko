#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
 void F_SBI(void){ // SET BIT IN I/O REGISTER
DataType R1= (getOpcode() & 0x01F8) >> 4; //identyfikacja numeru rejestru w przestrzeni I/O
int b = getOpcode() & 0x0007; //identyfikacja bitu
printf("0x%04X[0x%04X]: SBI R%d, %d\n", getPC(), getOpcode(), R1, b);
MEMD[IO_REGISTERS_IN_MEMD_OFFSET + R1]=MEMD[IO_REGISTERS_IN_MEMD_OFFSET + R1] | (1<<b);
setPC(getPC()+1);
addCounter(2);
}

