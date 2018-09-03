#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include "config.h"


void ADC_Init(void){

	// ANSEL = 0; ANS1 = 1;    // RA1/AN1 is ADC input
    // TRISA1 = 1;
    // CHS2 = 0; CHS1 = 0; CHS0 = 1; // Set channel (AN0, AN1, AN2, AN3, ...)
    
    ADCS2 = 0; ADCS1 = 1; ADCS0 = 0;    // Setting the A/D clock to Tosc * 32
    
    VCFG1 = 0; VCFG0 = 0;   // Set voltage ref to VDD

    ADFM = 1;   // 1: Right-justify the result; 0: Left-justify the result
    
    ADON = 1;
}

unsigned short ADC_Read(unsigned char channel){

    CHS = channel;

	switch(channel){
		case 0:
			TRISA0 = ANS0 = 1;
			break;
		case 1:
			TRISA1 = ANS1 = 1;
			break;
		case 2:
			TRISA2 = ANS2 = 1;
			break;
		case 3:
			TRISA3 = ANS3 = 1;
			break;
			// MUST AJUST TO LOCAL TRIS REGISTERS (TRISA, TRISB, ...) //////////////////////////////////////////////////////////
		// case 4:
		// 	TRISA4 = ANS4 = 1;
		// 	break;
		// case 5:
		// 	TRISA5 = ANS5 = 1;
		// 	break;
		// case 6:
		// 	TRISA6 = ANS6 = 1;
		// 	break;
		// default:
		// 	TRISA = ANSEL = 0;

			return 0;
	}
    
    // Waiting for Tacq >= 20µs (by far. At least much more than mentioned in the datasheet)
    __delay_ms(2);     
    
    // Starting the ADC
    GO_nDONE = 1;
    while(GO_nDONE == 1);

    return (unsigned short) (ADRESL + (ADRESH << 8));
}


#endif	/* ADC_H */

