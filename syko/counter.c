#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "types.h"
#include "mem_abs.h"
#include "gpio.h"



void setOC2(int b){
	if (b == 1){
		setBit(PORTB,7);
	}
	if (b == 0){
		clearBit(PORTB,7);
	}
}
void compareRegisters(void){
if (getMEMD(TCNT2)==0xff)
	setBit(TIFR,FLAG_TOV2); // Ustawienie TOV2
if (getMEMD(TCNT2)==getMEMD(OCR2))
	setBit(TIFR,FLAG_OCF2); // Ustawienie OCF2
}
void count(void){
setMEMD(TCNT2,getMEMD(TCNT2)+1); // Zwiekszenie licznika
compareRegisters();
}

