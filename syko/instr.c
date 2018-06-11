#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
#include "counter.h"



void F_RETI(void){
	printf("0x%04X[0x%04X]: RETI\n",getPC(),getOpcode());
	getPCfromStack();// przywrócenie PC ze stosu
	setBit(SREG,7); // ustawienie I w SREG
	addCounter(1);

}

void F_OUT(void){
   	DataType R= (getOpcode() & 0x01F0)>>4;
   	DataType A= ((getOpcode() & 0x0600)>>5) | (getOpcode() & 0x000F) ;
   	setMEMD(A+IO_REGISTERS_IN_MEMD_OFFSET,getRegister(R));
}
void F_SBI(void){ // SET BIT IN I/O REGISTER
	DataType R1= (getOpcode() & 0x00F8) >> 3; //identyfikacja numeru rejestru w przestrzeni I/O
	int b = getOpcode() & 0x0007; //identyfikacja bitu
	printf("0x%04X[0x%04X]: SBI R%d, %d\n", getPC(), getOpcode(), R1, b);
	setBit(IO_REGISTERS_IN_MEMD_OFFSET + R1,b);
	setPC(getPC()+1);
	addCounter(1);
}
void F_CBI(void){ // CLEAR BIT IN I/O REGISTER
	DataType R1= (getOpcode() & 0x00F8) >> 3; //identyfikacja numeru rejestru w przestrzeni I/O
	int b = getOpcode() & 0x0007; //identyfikacja bitu
	printf("0x%04X[0x%04X]: CBI R%d, %d\n", getPC(), getOpcode(), R1, b);
	clearBit(IO_REGISTERS_IN_MEMD_OFFSET + R1,b);
	setPC(getPC()+1);
	addCounter(1);
}

void F_NOP(void){
    	printf("0x%04X[0x%04X]: No operation...\n", getPC(), getOpcode());
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
void F_LDI(void){
	DataType R1=((getOpcode() & 0x00F0)>>4) + 16; 
	DataType R2=(getOpcode() & 0x0F00)>>4 | (getOpcode() & 0x000F); 
 	printf("0x%04X[0x%04X]: LDI R%d, %x \n", getPC(), getOpcode(), R1, R2); 	
	setRegister(R1, R2);
	addCounter(1);
}
void F_MOV(void){
	DataType R1= (getOpcode() & 0x01F0) >> 4;
	DataType R2= ((getOpcode() & 0x0200) >> 5) | (getOpcode() & 0x000F);
	printf("0x%04X[0x%04X]: MOV R%d, R%d\n",R1,R2);
	setRegister(R1,R2);
	
}

