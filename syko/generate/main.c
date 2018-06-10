#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//Linux compliance
#ifndef O_BINARY
    #define O_BINARY 0 
#endif

#define     MAX_ADDRESS             0xFFFF
#define     FILE_CODE               "file_code.bin"
#define 	FILE_DATA               "file_data.bin"

typedef unsigned short              CodeType;
typedef unsigned char               DataType;

CodeType    MEMC[MAX_ADDRESS+1];    //obszar pamieci kodu 
DataType    MEMD[MAX_ADDRESS+1];    //obszar pamieci danych

#define 	HTON(n)					\
			((n & 0x00ff)<<8) | ((n & 0xff00)>>8)
			

void saveMEMC(char *file, int size_f){        //zapisz zawartoœæ pamiêci kodu do pliku 
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("MEMC cannot open to write (%s)!\n", file);
        exit(-6);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Saved MEMC file (%s) in %dbytes\n", file, write(file_ptr, (void*)MEMC, size_f*sizeof(CodeType)));
    close(file_ptr);
}
void saveMEMD(char *file, int size_f){        //zapisz zawartoœæ pamiêci danych do pliku 
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("MEMC cannot open to write (%s)!\n", file);
        exit(-6);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Saved MEMC file (%s) in %dbytes\n", file, write(file_ptr, (void*)MEMD, size_f));
    close(file_ptr);
}
 
int main(int argc, char *argv[]){
	memset(MEMC, '\0', MAX_ADDRESS+1);
	MEMC[0]=HTON(0x1000);
	MEMC[1]=HTON(0x1000);
	MEMC[2]=HTON(0x1000);
	MEMC[3]=HTON(0x1000);
	MEMC[4]=HTON(0x1000);
	MEMC[5]=HTON(0x1000);
	MEMC[6]=HTON(0x1000);
	MEMC[7]=HTON(0x6001);
	MEMC[18]=HTON(0x7000);
	MEMC[19]=HTON(0x0020);
	MEMC[20]=HTON(0x7000);
	MEMC[21]=HTON(0x0023);
	MEMC[32]=HTON(0x20C7);
	MEMC[33]=HTON(0x31B6);
	MEMC[34]=HTON(0x8000);
	MEMC[35]=HTON(0x30C6);
	MEMC[36]=HTON(0x31B7);
	MEMC[37]=HTON(0x8000);

	MEMD[0x0000]=0x01;
	MEMD[0x005f]=0x80; // SREG bit I
	MEMD[0x0057]=0xc0; // TIMSK overflow&match intterupt enable

	saveMEMC(FILE_CODE, 40);
	saveMEMD(FILE_DATA, 0xff);
}
