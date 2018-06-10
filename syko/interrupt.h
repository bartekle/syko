#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

void initInterrupt(void);
void checkInterrupt(unsigned int counter);


//2018.05.16---:
void update_EIMSK(DataType r);
//---2018.05.16

#endif //__INTERRUPTS_H__
