#ifndef ADC_H
#define	ADC_H

#include <xc.h>

#include "config.h"


void ADC_Init(void){
    ADCS2 = 1; ADCS1 = 0; ADCS0 = 0;    // Setting the A/D clock to Tosc * 16
    
    ADFM = 0;   // 1: Right-justify the result; 0: Left-justify the result
    VCFG = 0;   // Set voltage ref to VDD
    CHS1 = 0; CHS0 = 0; // Set channel (AN0, AN1, AN2, AN3)
    
    ADON = 1;
}

unsigned short ADC_Read_8_bits(void){
    // In the actual application (keypad read), we need only a low-precision value, so
    // this func returns only the 8 MSBs out of 10 bits read by the ADC module.
    

    // Waiting for Tacq >= 20µs (by far. At least much more than mentioned in the datasheet)
    __delay_ms(10);     
    
    // Starting the ADC
    ADCON0bits.GO_nDONE = 1;
    while(GO_nDONE == 1);

    // ADFM = 0;    (See 'ADC_Init()')
    return ADRESH;  // Only the 8 MSBs (bit 9 to bit 2 of the 10-bit result)
}


#endif	/* ADC_H */

