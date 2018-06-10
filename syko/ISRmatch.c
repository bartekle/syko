#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
void cmpmatch_ISR(void){
setOC2(1); // włączenie OUTPUT
MEMD[TIFR]=MEMD[TIFR] & (~(1<<7)); // wyzerowanie flagi compare match OCF2
setPC((getMEMD(SPH) << 8) | (getMEMD(SPL)));// przywrócenie PC ze stosu
setMEMD(SREG,getMEMD(0x0060)); // przywrócenie SREG ze stosu
printf("RET, PC <-- STACK");
addCounter(4);
}
