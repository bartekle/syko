#ifndef __TYPES_H__
#define __TYPES_H__

//definicje nowych typow danych
typedef unsigned char               DataType;
typedef unsigned short              CodeType;
typedef unsigned short              AddressType;
typedef unsigned int                CounterType;

//najwieksze wartosci 
#define MAX_ADDRESS                 0xFFFF
#define MAX_DATA_VAL                0xFF

//Numer ostatniego rejestru
#define REGISTERS_COUNT             (0x001F-0x0000)+1
#define MAX_REGISTER                REGISTERS_COUNT-1
#define IO_REGISTERS_COUNT          (0x005F-0x0020)+1
#define MAX_IO_REGISTERS            IO_REGISTERS_COUNT-1
#define EIO_REGISTERS_COUNT         (0x00FF-0x0060)+1
#define MAX_EIO_REGISTERS           EIO_REGISTERS_COUNT-1

#define GEN_REGISTERS_IN_MEMD_OFFSET    0x0000
#define IO_REGISTERS_IN_MEMD_OFFSET     GEN_REGISTERS_IN_MEMD_OFFSET+REGISTERS_COUNT
#define EIO_REGISTERS_IN_MEMD_OFFSET    IO_REGISTERS_IN_MEMD_OFFSET+IO_REGISTERS_COUNT



//Znaczenie flag
#define FLAG_C                      0x01
#define FLAG_I                      0x80
#define FLAG_OCF2                   7
#define FLAG_TOV2		    6
#define MAX_SIMULATION_STEPS        1000
//Adresy rejestrów
#define TIFR 						0x0056
#define TIMSK						0x0057
#define PORTB 						0x0038
#define TCNT2						0x0044
#define OCR2						0x0043
#define SREG						0x005f
#define SPL                                             0x005d
#define SPH						0x005e
#define OVERFLOW_SR                                     0x0012
#define CMPMATCH_SR					0x0014


#endif //__TYPES_H__
