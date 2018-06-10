#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
void overflow_ISR(void){
setOC2(0); // wyłączenie OUTPUT                                               SBI PORTB, 7
resetCounterFlagsRegister(FLAG_TOV2); // wyzerowanie flagi overflow TOV2      CLI TIFR, 6  
setPC((getMEMD(SPH) << 8) | (getMEMD(SPL)));// przywrócenie PC ze stosu       RETI
setMEMD(SREG,getMEMD(0x0060)); // przywrócenie SREG ze stosu
printf("RET, PC <-- STACK");
addCounter(4);
}
