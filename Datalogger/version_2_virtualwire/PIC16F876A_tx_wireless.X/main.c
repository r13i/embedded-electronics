/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - 
*/


#include <xc.h>
#include <stdio.h>

#include "config.h"
#include "adc.h"
#include "virtualwire.h"

#define SEND_EVERY_MS 2000
#define SENSOR_ID_0 0
#define SENSOR_ID_1 1

void interrupt global_isr(void){
	if(TMR0IF)
		vw_isr_tmr0();
}

void main(void)
{
    ADC_Init();
	vw_setup(200);

    // We format the message to be sent as "DEVICE_ID,VALUE" (Notice the comma separator)
    char adcBuffer[7];  // ID + Comma separator + ADC value
	
    while(1)
	{
        unsigned long adcValue_0 = (unsigned long) ADC_Read(0) * 100 / 1024;
        unsigned long adcValue_1 = (unsigned long) ADC_Read(1) * 100 / 1024;
        
        sprintf(adcBuffer, "%u,%lu", SENSOR_ID_0, adcValue_0);
        vw_send(adcBuffer, sizeof(adcBuffer) - 1);
        
        __delay_ms(10);     // Wait to make sure previous message has been correctly sent
        
        sprintf(adcBuffer, "%u,%lu", SENSOR_ID_1, adcValue_1);
        vw_send(adcBuffer, sizeof(adcBuffer) -1);
        
        // TODO : Switch from using __delay_ms to interruptible mode (see TIMER1 or TIMER2)
        __delay_ms(SEND_EVERY_MS);
    }
	
}
