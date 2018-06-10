#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_ADD2(void){
    DataType R1=getOpcode() & 0x000F;                              //identyfikacja numeru rejestru arg. 1
    DataType R2=(getOpcode() & 0x00F0)>>4;                         //identyfikacja numeru rejestru arg. 2

    printf("0x%04X[0x%04X]: ADD R%d, MEMD[R%d]\n", getPC(), getOpcode(), R1, R2);

    if((getRegister(R1) + getMEMD(getRegister(R2))) > MAX_DATA_VAL)
        setFlagsRegister(FLAG_C);                                   //ustawienie flagi przeniesienia
    else
        resetFlagsRegister(FLAG_C);                                 //wykasowanie flagi przeniesienia

    setRegister(R1, (getRegister(R1) + getMEMD(getRegister(R2))) % MAX_DATA_VAL);    //w�a�ciwe obliczenie

    setPC(getPC()+1);                                              //zwi�kszenie licznika rozkaz�w

    addCounter(4);
}
