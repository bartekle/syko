#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"
#include "instr.h"
//naglowki poszczegolnych opcodow 


//wzorce opcodow 
#define ID_NOP      0x01
#define ID_SBI 	    0x02
#define ID_CBI      0x03
#define ID_CLI	    0x04
#define ID_SEI      0x05
#define ID_JMP_K    0x06
#define ID_JMP_MEMC 0x07
#define ID_RETI     0x08
#define ID_LDI	    0x09
#define ID_MOV      0x0A

void doInstr(CodeType T){
    switch((T & 0xF000)>>12){   //wy�uskanie w�a�ciwego kodu operacji
        case 	ID_JMP_K:
		F_JMP_K();
            break;
        case 	ID_SBI:
		F_SBI();
            break;
        case 	ID_CBI:
		F_CBI();
            break;
        case 	ID_CLI:
		F_CLI();
            break;
        case 	ID_SEI:
		F_SEI();
            break;
	case	ID_NOP:
		F_NOP();
	    break;
	case	ID_JMP_MEMC:
		F_JMP_MEMC();
	    break;
	case	ID_RETI:
		F_RETI();
	    break;
	case 	ID_LDI:
		F_LDI();
	    break;
	case	ID_MOV:
		F_MOV();
	    break;
        default:
            printf("Unknown opcode at PC=0x%08lx! (T=0x%04lx)\r\n", getPC(), T);
            saveCPUState();
            exit(-1);
    }
}
