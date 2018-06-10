#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
void F_CALL(void){
	DataType R= getOpcode() & 0x000F; // identyfikacja numeru rejestru w ktorym znajduje sie adres PC
	setMEMD(0x0062,getPC() & 0xFF00); // pierwsze 8 bitów PC
	setMEMD(0x0061,getPC() & 0x00FF); // drugie 8 bitów PC
	setMEMD(0x0060,SREG); // rejestr statusu CPU
	setPC(getRegister(R));
}
