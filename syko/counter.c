#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "types.h"
#include "mem_abs.h"



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
void updateOCR2(DataType R){
setMEMD(OCR2,R);
}
/*unsigned int setPrescaler(void){
unsigned int temp= getMEMD(TCCR2) & 0x07;
	switch(temp){
		case 2:
			return 8;
			break;
		case 3:
			return 64;
			break;
		case 4:
			return 256;
			break;
		case 5:
			return 1024;
			break;
		default:
			return 1;
		
	}
}
*/

