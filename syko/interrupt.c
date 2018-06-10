#include <stdio.h>
#include "types.h"
#include "mem_abs.h"


void initInterrupt(void){
	//...
}
void checkInterrupt(CounterType counter){
	if((getMEMD(SREG) & 0x80)!=0){		   //SREG - bit I: "Global Interrupt Enable", jezeli ustawiony to zezwolno na jakie kolwiek przerwania
		if((getMEMD(TIMSK) & 0xc0)!=0){			//czy przerwania od Counter2 są włączone //"The low level of INT0 generates an interrupt request"
			if((getMEMD(TIFR) & 0x40) !=0){
						printf("----------------------Prepare to start user OVERFLOW routine\r\n");
						clearBit(SREG,7);
						movePConStack();    // przenieś PC na stos
						//moveSREGonStack();  // przenieś SREG na stos
						setPC(OVERFLOW_SR);
						return;
			}

			if((getMEMD(TIFR) & 0x80) !=0){
						printf("----------------------Prepare to start user COMPARE MATCH routine\r\n");
						clearBit(SREG,7);
						movePConStack();    // przenieś PC na stos
						//moveSREGonStack();  // przenieś SREG na stos
						setPC(CMPMATCH_SR);
						return;

		       }
		       
		}
	}
}

