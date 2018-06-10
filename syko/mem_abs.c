#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "types.h"


//Linux compliance
#ifndef O_BINARY
    #define O_BINARY 0 
#endif


//#define GEN_REGISTERS_IN_MEMD_OFFSET    0x0000
//#define IO_REGISTERS_IN_MEMD_OFFSET     GEN_REGISTERS_IN_MEMD_OFFSET+REGISTERS_COUNT
//#define EIO_REGISTERS_IN_MEMD_OFFSET    IO_REGISTERS_IN_MEMD_OFFSET+IO_REGISTERS_COUNT

CodeType    MEMC[MAX_ADDRESS+1];    //obszar pami�ci kodu 
DataType    MEMD[MAX_ADDRESS+1];    //obszar pami�ci danych
DataType    *GEN_REG=(DataType*)(&(MEMD[GEN_REGISTERS_IN_MEMD_OFFSET]));    //deklaracja miejsca przechowywania rejestr�w ogolnego przeznaczenia
DataType    *IO_REG=(DataType*)(&(MEMD[IO_REGISTERS_IN_MEMD_OFFSET]));      //deklaracja miejsca przechowywania rejestr�w IO
DataType    *EIO_REG=(DataType*)(&(MEMD[EIO_REGISTERS_IN_MEMD_OFFSET]));    //deklaracja miejsca przechowywania rejestr�w EIO

AddressType   PC;                   //licznik rozkaz�w
AddressType   stack_pointer= 103;
//2018.05.16---:
//DataType    FLAGS;                  //flagi procesora
//---2018.05.16
CounterType counter;                //licznik wykonanych cykli

void dumpMEMConfiguration(void){
    printf("REGISTERS_COUNT:     0x%08x\n", REGISTERS_COUNT);
    printf("MAX_REGISTER:        0x%08x\n", MAX_REGISTER);
    printf("IO_REGISTERS_COUNT:  0x%08x\n", IO_REGISTERS_COUNT);
    printf("MAX_IO_REGISTERS:    0x%08x\n", MAX_IO_REGISTERS);
    printf("EIO_REGISTERS_COUNT: 0x%08x\n", EIO_REGISTERS_COUNT);
    printf("MAX_EIO_REGISTERS:   0x%08x\n", MAX_EIO_REGISTERS);
    printf("GEN_REGISTERS_IN_MEMD_OFFSET: 0x%08x\n", GEN_REGISTERS_IN_MEMD_OFFSET);
    printf("IO_REGISTERS_IN_MEMD_OFFSET:  0x%08x\n", IO_REGISTERS_IN_MEMD_OFFSET);
    printf("EIO_REGISTERS_IN_MEMD_OFFSET: 0x%08x\n", EIO_REGISTERS_IN_MEMD_OFFSET);
}
void loadPC(char *file){          //�adowanie nowej warto�ci PC
    int file_ptr;
    AddressType tPC;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("PC file not found (%s)!\n", file);
        exit(-2);
    }
    lseek(file_ptr, 0, SEEK_SET);
    printf("Read PC file (%s) in %dbytes ", file, read(file_ptr, &tPC, sizeof(AddressType)));
    PC=(tPC & 0xFF00)>>8 | (tPC & 0x00FF)<<8;    //Endianess correction
    printf("[PC=0x%04X]\n", PC);
    close(file_ptr);
}
void loadCounter(char *file){          //�adowanie ostatnio zapisanego licznika cykli 
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("Counter file not found (%s)!\n", file);
        exit(-2);
    }
    lseek(file_ptr, 0, SEEK_SET);
    printf("Read counter file (%s) in %dbytes ", file, read(file_ptr, &counter, sizeof(CounterType)));
    printf("[counter=%05d]\n", counter);
    close(file_ptr);
}
void loadMEMC(char *file){          //�adowanie pami�ci kodu z pliku 
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("MEMC file not found (%s)!\n", file);
        exit(-3);
    }
    lseek(file_ptr, 0, SEEK_SET);
    printf("Read MEMC (%s) file in %dbytes\n", file, read(file_ptr, (void*)MEMC, MAX_ADDRESS+1));
    close(file_ptr);
}
void loadMEMD(char *file){        //�adowanie pami�ci danych z pliku
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("MEMD file not found (%s)!\n", file);
        exit(-4);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Read MEMD (%s) file in %dbytes\n", file, read(file_ptr, (void*)MEMD, MAX_ADDRESS+1));
    close(file_ptr);
}
void savePC(char *file){        //Zapisz warto�c PC
    int file_ptr;
    AddressType tPC=PC;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("PC cannot open to write (%s)!\n", file);
        exit(-5);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    tPC=(PC & 0xFF00)>>8 | (PC & 0x00FF)<<8;		//Endianess correction
    printf("Write PC (%s) file in %dbytes [PC=0x%04X]\n", file, write(file_ptr, &tPC, sizeof(AddressType)), PC);
    close(file_ptr);
}
void saveCounter(char *file){        //Zapisz warto�c licznika cykli
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("Cannot open to write (%s)!\n", file);
        exit(-5);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Write counter (%s) file in %dbytes [counter=%05d]\n", file, write(file_ptr, &counter, sizeof(CounterType)), counter);
    close(file_ptr);
}
void saveMEMD(char *file){        //zapisz zawarto�� pami�ci danych do pliku 
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("MEMD cannot open to write (%s)!\n", file);
        exit(-6);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Saved MEMD file (%s) in %dbytes\n", file, write(file_ptr, (void*)MEMD, MAX_ADDRESS));
    close(file_ptr);
}
CodeType getMEMC(AddressType p){
    CodeType t=(MEMC[p] & 0xFF00)>>8 | (MEMC[p] & 0x00FF)<<8;		//Endianess correction
    return t;
}
DataType getMEMD(AddressType p){
    return MEMD[p];
}
//2018.05.16---:
void setMEMD(AddressType p, DataType v){
    MEMD[p]=v;
}
//---2018.05.16
void setPC(AddressType v){
    PC=v;
}
AddressType getPC(void){
    return PC;
}
CodeType getOpcode(void){
    return getMEMC(PC);
}
CounterType getCounter(void){
    return counter;
}
void addCounter(CounterType n){
    counter+=n;
}
DataType getRegister(int n){
    return GEN_REG[n];
}
void setRegister(int n, DataType v){
    GEN_REG[n]=v;
}
//2018.05.16---:
void setFlagsRegister(int b){
    MEMD[SREG]=MEMD[SREG] | (1<<b);
}
void resetFlagsRegister(int b){
    MEMD[SREG]=MEMD[SREG] & (~(1<<b));
}
int getFlagsRegister(int b){
	//printf("SREG=%d\n", SREG);
	//printf("MEMD[SREG]=%d\n", MEMD[SREG]);
	//printf("b=%d\n", b);
  
	if((MEMD[SREG] & b)!=0)
		return 1;
	return 0;
}
void setBit(AddressType p, int b){
    MEMD[p]=MEMD[p] | (1<<b);
}
void clearBit(AddressType p,int b){
    MEMD[p]=MEMD[p] & (~(1<<b));
}
void getBit(AddressType p, int b){
    if((MEMD[p] & b)!=0)
	return 1;
    return 0;
}
void movePConStack(void){

	MEMD[stack_pointer--]= (getPC() & 0xFF00) >> 8;
	MEMD[stack_pointer--]= getPC() & 0x00FF;
}
void getPCfromStack(void){
	PC = (MEMD[++stack_pointer]) | (MEMD[++stack_pointer] << 8);

}
AddressType getSP(void){
return stack_pointer;
}
