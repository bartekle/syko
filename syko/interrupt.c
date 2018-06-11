#include <stdio.h>
#include "types.h"
#include "mem_abs.h"



void checkInterrupt(CounterType counter){
	if((getMEMD(SREG) & 0x80)!=0){		   //SREG - bit I: "Global Interrupt Enable", jezeli ustawiony to zezwolno na jakie kolwiek przerwania
		if((getMEMD(TIMSK) & 0xc0)!=0){			//czy przerwania od Counter2 są włączone?
			if((getMEMD(TIFR) & 0x40) !=0){		//czy ustawiona jest flaga przepełnienia?
						printf("----------------------Prepare to start user OVERFLOW routine\r\n");
						clearBit(SREG,7); // wylacz przerwania na czas obsługi zdarzenia
						clearBit(TIFR,FLAG_TOV2);// wyczysc flage przepelnienia
						movePConStack();    // przenieś PC na stos
						setPC(OVERFLOW_SR); // ustaw adres handlera przepełneinia
						return;
			}

			if((getMEMD(TIFR) & 0x80) !=0){           // czy ustawiona jest flaga compare match?
						printf("----------------------Prepare to start user COMPARE MATCH routine\r\n");
						clearBit(SREG,7); // wylacz pzerwania na czas obslugi zdarzenia
						clearBit(TIFR,FLAG_OCF2); // wyczysc flage compare match
						movePConStack();    // przenieś PC na stos
						setPC(CMPMATCH_SR); // ustaw adres handlera compare match
						return;

		       }
		       
		}
	}
}

