/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - mohamed_amir_alaa.belmekki@g.enp.edu.dz 
*/

#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include "config.h"


void ADC_Init(void){
    // Helper function to setup and configure the 10-bit ADC
    
    ADCS1 = 1; ADCS0 = 0;    // Setting the A/D clock to Tosc * 32
    
    // Setup Analog input to AN0, AN1, and AN3 (Notice that AN3 is not actually used in this application)
    PCFG3 = 0; PCFG2 = 1; PCFG1 = 0; PCFG0 = 0;
    
    ADFM = 1;   // 1: Right-justify the result; 0: Left-justify the result
    
    ADON = 1;   // Set to ON
}

unsigned short ADC_Read(unsigned char channel){
    // Read the voltage level from specified channel with the 10-bit ADC
	// In this application, only channels 0 (AN0) and 1 (AN1) are used

	if(channel > 1){
        TRISA0 = TRISA1 = 0;
		return 0;
    }

    // Setup the ADC channel
    ADCON0bits.CHS = channel;


    // Setup the corresponding pin to ANALOG input
    switch(channel){
    	case 0:
    		TRISA0 = 1;
    		break;
    	case 1:
    		TRISA1 = 1;
    		break;
    	default:
            // Should not get here
            break;
    }

    
    // Waiting for (T_acquisition >= 20µs) (by far. At least much more than mentioned in the datasheet)
    __delay_ms(2);
    
    // Starting the ADC
    ADCON0bits.GO_nDONE = 1;
    
    // Wait till the operation is done
    while(GO_nDONE == 1);

    // Return the 10-bit result
    return (unsigned short) (ADRESL + (ADRESH << 8));
}


#endif	/* ADC_H */

