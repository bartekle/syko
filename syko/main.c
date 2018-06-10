#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"
#include "gpio.h"
#include "instr.h"
#include "counter.h"

#define FILE_COUNTER            "file_counter.bin"
#define FILE_PC                 "file_pc.bin"
#define FILE_DATA               "file_data.bin"
#define FILE_CODE               "file_code.bin"
#define FILE_GPIO_IN            "file_gpio_in.txt"
#define FILE_GPIO_OUT           "file_gpio_out.txt"

unsigned int simulation_start=0;
unsigned int simulation_end=0;
void saveCPUState(void){
    saveMEMD(FILE_DATA);        //Zapisz zawarto�� pami�ci danych do pliku
    savePC(FILE_PC);            //Zapisz warto�c PC
    saveCounter(FILE_COUNTER);  //Zapisz liczbe wykonanych cykli
}
int main(int argc, char *argv[]) {
    unsigned int counter=0, max_counter=0;      //pomocnicza liczba wykonanych instrukcji i zadana liczba instrukcji do wykonania
    CodeType T;                                 //zmienna pomocnicza - ma przechowywa� opcode instrukcji
//2018.05.16---:
	CounterType Ctemp;
//---2018.05.16

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    loadMEMC(FILE_CODE);                //�adowanie pami�ci kodu z pliku 
    loadMEMD(FILE_DATA);                //�adowanie pami�ci danych z pliku (w tym rejestr�wm)
    loadPC(FILE_PC);                    //�adowanie warto�ci PC
    loadCounter(FILE_COUNTER);          //�adowanie licznika cykli
    //dumpMEMConfiguration();
    
    simulation_start=getCounter();

    //printf("MEMD[SREG=0x%04x]=0x%02x\n", SREG, getMEMD(SREG));
    //printf("getFlagsRegister(FLAG_I)=%d\n", getFlagsRegister(FLAG_I));
    
    if(argc>1){	                        //pierwszy parametr wywolania okresla liczbe instrukcji do wykonania
        max_counter=strtoul(argv[1], NULL, 10);
        simulation_end=max_counter+simulation_start;
    }
    if(max_counter==0){
        simulation_end=simulation_start+1;     //nie podanie argumentu wywolania lub b�edne jego podanie - ustala wykonanie jednego cyklu
    }
    if(max_counter>MAX_SIMULATION_STEPS){
        simulation_end=simulation_start+MAX_SIMULATION_STEPS;//w pojedycznczej symulacji nie dopuszczamy wiecej niz MAX_SIMULATION_STEPS krokow
    }
    //dumpGPIOchangesIN();

    for(;;){
        printf("{%05d}",getCounter());   //numer cyklu
	Ctemp=getCounter();
	count();
	checkInterrupt(Ctemp);           //sprawd� czy trzeba wygenerowac przerwanie
        T=getOpcode();                   //T=opcode operacji (w��cznie z arg. wbudowanym)
        doInstr(T);                     //wykonaj instrukcje
        printf("Wartosc rejestru TCNT2: %d\n",getMEMD(TCNT2));
	printf("Stack_pointer = %d\n",getSP());
	
       
        if(getCounter()>=simulation_end){  //czy wykonano zadan� liczb� cykli
            saveCPUState();
            return 0;
        }
    }

    printf("Bledne wykonanie emulacji (PC=0x%08lx, T=0x%08lx)\r\n", getPC(), T);
    saveCPUState();                     //!!! - Tu niepowinnismy si� nigdy znale��
    return -2;
}
