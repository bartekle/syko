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
	
	MEMD[0x0000]=0x00;
	MEMD[0x005f]=0x00; // SREG bit I
	MEMD[0x0057]=0x00; // TIMSK overflow&match intterupt enable

	saveMEMC(FILE_CODE, 40);
	saveMEMD(FILE_DATA, 0xff);
}
