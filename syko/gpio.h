#ifndef __GPIO_H__
#define __GPIO_H__

void loadGPIOchanges(char *file, unsigned int cycle_start, unsigned int cycle_end);
void saveGPIOchanges(char *file, unsigned int cycle_start, unsigned int cycle_end);
void dumpGPIOchangesIN(void);
unsigned char getGPIO(int num, unsigned int counter);


#endif //__GPIO_H__
