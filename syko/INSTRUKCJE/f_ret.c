#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_RET(void){
setPC((getMEMD(SPH) << 8) | (getMEMD(SPL)));// przywrócenie PC ze stosu
setMEMD(SREG,getMEMD(0x0060)); // przywrócenie SREG ze stosu
setFlagsRegister(FLAG_I);
addCounter(4);

}
