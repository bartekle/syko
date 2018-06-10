#include <stdio.h>
#include "types.h"

#include "mem_abs.h"

//2018.05.16---:
#include "avr_sfr.h"

void F_OUT(void){
    DataType R=(getOpcode() & 0x01F0)>>4;                             //identyfikacja numeru rejestru 
    DataType A=((getOpcode() & 0x0600)>>5) | (getOpcode() & 0x000F); //identyfikacja miejsca w I/O

    printf("0x%04X[0x%04X]: OUT I/O(0x%x), R%d\n", getPC(), getOpcode(), A, R);

    switch(A+IO_REGISTERS_IN_MEMD_OFFSET){                             //SFR access analisys
        case EIMSK:
            update_EIMSK(getRegister(R));
            break;
        case EIFR:
            //...
            break;
        //...
        default:
            printf("Access to unknown SFR (I/O) at 0x%02x! (PC=0x%08lx)\r\n", A, getPC());
    }

    setPC(getPC()+1);                                                  //zwiêkszenie licznika rozkazów

    addCounter(1);
}
//---2018.05.16
void F_OUT(void){
   DataType R= (getOpcode() & 0x001F);
   DataType A= (getOpcode() & 0x3F00)>>8;
   setMEMD(A+IO_REGISTERS_IN_MEMD_OFFSET,getRegister(R));
}
