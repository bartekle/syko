#ifndef __MEM_ABS_H__
#define __MEM_ABS_H__

void dumpMEMConfiguration(void);

void loadCounter(char *file);

void loadPC(char *file);
void savePC(char *file);
void loadMEMC(char *file);
void loadMEMD(char *file);
void saveMEMD(char *file);
void saveCounter(char *file);
void loadCounter(char *file);

CodeType getMEMC(AddressType p);
DataType getMEMD(AddressType p);
void setMEMD(AddressType p, DataType v);

void setPC(AddressType v);
AddressType getPC(void);
CodeType getOpcode(void);

CounterType getCounter(void);
void addCounter(CounterType n);

DataType getRegister(int n);
void setRegister(int n, DataType v);

void setFlagsRegister(int b);
void resetFlagsRegister(int b);
int getFlagsRegister(int b);
void storeCPUstate(void);
void setBit(AddressType p, int b);
void clearBit(AddressType p, int b);
void movePConStack(void);
void getPCfromStack(void);
AddressType getSP(void);
int getOC2state(void);
#endif //__MEM_ABS_H__
