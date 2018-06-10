//2018.05.16---:
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "types.h"
#include "mem_abs.h"

//Linux compliance
#ifndef O_BINARY
    #define O_BINARY 0 
#endif

#define MAX_LINE_GPIO_FILE	128
#define MAX_SIMULATION_STEPS 1000
#define MAX_GPIO 1
//macierz: 
//os x: numer GPIO, 
//os y: krok symulacji (w danym wywolaniu symulacji system przejdzuie wylacznie po tych krokach)
//      uwaga: krok w ofsssecie 0 to 'simulation_start' z main
//             ostatni wpis to 'simulation_start'+MAX_SIMULATION_STEPS czyli 'simulation_end'
CounterType gpio_story_from_step, gpio_story_to_step;
unsigned char gpio_story_in[MAX_GPIO*MAX_SIMULATION_STEPS];		//utrzymujemy informacje co bedzie sie dzialo z GPIO numer x w kolejnych cyklach
unsigned char gpio_story_out[MAX_GPIO*MAX_SIMULATION_STEPS];	//utrzymujemy informacje co sie dzialo z GPIO numer x w kolejnych cyklach


void dumpGPIOchangesIN(void){
    unsigned int i,j;
    for(j=0; j<MAX_SIMULATION_STEPS; j++){
        printf("T=%05d: ", j+gpio_story_from_step);
        for(i=0; i<MAX_GPIO; i++){
            printf("%02x,", gpio_story_in[i+j*MAX_GPIO]);
        }
        printf("\n");
    }
}

int myreadline(int file_ptr, unsigned char *buffer, int size){
    //zwraca 0 gdy koniec pliku lub nie mozna czytac 
    //w buffer jest zawsze string zakonczony zerem, gdy nie udalo sie przeczytac nic to i tak jest tam string zakonczony zerem  
    int p=0;
    unsigned char c;
    
    memset(buffer, '\0', size);
    for(;;){
        int n=read(file_ptr, &c, 1);
        if(n<1){
            buffer[p]='\0';
            return 0;
        }
        if(p==0){
            if((c==0x0D)||(c==0x0A)){
                continue;
            }
        }
        if(n==0){
            buffer[p]='\0';
            return 0;
        }
        buffer[p]=c;
        p++;
        if(p>size){
            buffer[size-1]='\0';
            return size;
        }
        if((c==0x0D)||(c==0x0A)){
            buffer[p-1]='\0';
            return p-1;
        }
    }
    return 0;
}

void setGPIOonestep(int mgpio, unsigned int row, int mstate){
    gpio_story_in[(unsigned int)mgpio+(unsigned int)row*MAX_GPIO]=mstate;
}
unsigned char getGPIOonestep(int mgpio, unsigned int row){
    return gpio_story_in[(unsigned int)mgpio+(unsigned int)row*MAX_GPIO];
}

void updateGPIOstateFromStep(int mgpio, CounterType mtime, int mstate){
//od chwili 'mtime' do 'INF' zmien stan plinu 'mgpio' na 'mstate'
    CounterType i,j,k;

    if(gpio_story_from_step>mtime){
        i=0;
    }else{
        i=mtime-gpio_story_from_step;
    }
    k=MAX_SIMULATION_STEPS;	
    for(;;){
        setGPIOonestep(mgpio, i, mstate);
        i++;
        if(i>k)
            break;
    }
}

void loadGPIOchanges(char *file, CounterType from_step, CounterType to_step){
    int file_ptr;
    AddressType tPC;
    int i,j;
    CounterType mtime;
    int mgpio;
    int mstate;
    unsigned char my_line[MAX_LINE_GPIO_FILE];

    gpio_story_from_step=from_step;
    gpio_story_to_step=to_step;

    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("PC file not found (%s)!\n", file);
        exit(-2);
    }

    memset(gpio_story_in, 0xff, sizeof(gpio_story_in));

    for(;;){
        int n=myreadline(file_ptr, my_line, MAX_LINE_GPIO_FILE); //analiza pojedynczej linii pliku wej.
        if(strlen(my_line)==0)                                   //czy nie jest pusta linia
            continue;
        if(my_line[0]=='#')         //czy linia nie zaczyna sie od komentarza
            continue;
        sscanf(my_line, "%d,%d,%d", &mtime, &mgpio, &mstate);
        updateGPIOstateFromStep(mgpio, mtime, mstate);
        if(n<=0)                    //koniec danych w pliku we
            break;
    }
    close(file_ptr);
}
unsigned char getGPIO(int num, CounterType counter){
    return getGPIOonestep(num, counter-gpio_story_from_step);
}
void saveOC2changes(char *file,CounterType step,int state){
	FILE *f = fopen(file, "a");
	if (f == NULL)
	{
   		printf("Error opening file!\n");
    		exit(1);
	}

	fprintf(f,"%d,%d\n",step,state);
	fclose(f);

}

