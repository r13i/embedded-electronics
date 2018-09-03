/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - 
*/


#include <xc.h>
#include <stdio.h>

#include "config.h"
#include "virtualwire.h"


void interrupt global_isr(void){
	if(TMR0IF)
		vw_isr_tmr0();
}

void delay(unsigned int delay){
	while(delay--);
}

void main(void)
{
	// const char text[] = "Hello from PIC";

	vw_setup(200);

    unsigned char j = 0;
    
	while(1)
	{
		//vw_send(text, sizeof(text)-1);
        // delay(20000);
        
        for(j = 0; j < 100 ; ++j){
            char buffer[5];
            sprintf(buffer, "%d", j);
            
            vw_send(buffer, sizeof(buffer) - 1);
            delay(20000);
        }
	}
	
}
