#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
#include "counter.h"

void F_CALL(void){
	DataType R= getOpcode() & 0x000F; // identyfikacja numeru rejestru w ktorym znajduje sie adres PC
	setMEMD(0x0062,getPC() & 0xFF00); // pierwsze 8 bitów PC
	setMEMD(0x0061,getPC() & 0x00FF); // drugie 8 bitów PC
	setMEMD(0x0060,SREG); // rejestr statusu CPU
	setPC(getRegister(R));
}

void F_RETI(void){
	printf("0x%04X[0x%04X]: RETI\n",getPC(),getOpcode());
	getPCfromStack();// przywrócenie PC ze stosu
	setBit(SREG,7); // ustawienie I w SREG
	addCounter(4);

}

void F_OUT(void){
   	DataType R= (getOpcode() & 0x001F);
   	DataType A= (getOpcode() & 0x3F00)>>8;
   	setMEMD(A+IO_REGISTERS_IN_MEMD_OFFSET,getRegister(R));
}
void F_SBI(void){ // SET BIT IN I/O REGISTER
	DataType R1= (getOpcode() & 0x03F8) >> 3; //identyfikacja numeru rejestru w przestrzeni I/O
	int b = getOpcode() & 0x0007; //identyfikacja bitu
	printf("0x%04X[0x%04X]: SBI R%d, %d\n", getPC(), getOpcode(), R1, b);
	setBit(IO_REGISTERS_IN_MEMD_OFFSET + R1,b);
	setPC(getPC()+1);
	addCounter(2);
}
void F_CBI(void){ // CLEAR BIT IN I/O REGISTER
	DataType R1= (getOpcode() & 0x03F8) >> 3; //identyfikacja numeru rejestru w przestrzeni I/O
	int b = getOpcode() & 0x0007; //identyfikacja bitu
	printf("0x%04X[0x%04X]: CBI R%d, %d\n", getPC(), getOpcode(), R1, b);
	clearBit(IO_REGISTERS_IN_MEMD_OFFSET + R1,b);
	setPC(getPC()+1);
	addCounter(2);
}

void F_NOP(void){
    	printf("0x%04X[0x%04X]: No operation!\n", getPC(), getOpcode());
	setPC(getPC()+1);
    	addCounter(1);
}
void F_JMP_MEMC(void){
    	printf("0x%04X[0x%04X]: JMP MEMC[0x%04X]=0x%04X\n", getPC(), getOpcode(), getPC()+1, getMEMC(getPC()+1));
    	setPC(getMEMC(getPC()+1));
    	addCounter(1);
}
void F_JMP_K(void){
	AddressType p= getOpcode() & 0x000F;
	printf("0x%04X[0x%04X]: JMP 0x%04X=0x%04X\n", getPC(), getOpcode(), p, getMEMC(p));
	setPC(p);
    	addCounter(1);
}
void F_CLI(void){
	resetFlagsRegister(FLAG_I);
	printf("0x%04X[0x%04X]: CLI",getPC(),getOpcode());
	setPC(getPC()+1);
	addCounter(1);
}
void F_SEI(void){
	setFlagsRegister(FLAG_I);
	printf("0x%04X[0x%04X]: SBI",getPC(),getOpcode());
	setPC(getPC()+1);
	addCounter(1);
}
