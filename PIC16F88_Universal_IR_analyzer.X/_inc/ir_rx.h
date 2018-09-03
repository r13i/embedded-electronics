#ifndef IR_RX_H
#define	IR_RX_H


// Some error occured during the compilation, so the functions are directly
// implemented here.
/*
#include <xc.h>


unsigned char IR_GetStateDuration(unsigned char state);

void IR_Demodulate(unsigned char fallTime, unsigned char riseTime);

unsigned long IR_Detect(void)
*/

#include <xc.h>

#include "ir_rx.h"

#include "config.h"
#include "uart.h"
#include "tmr0.h"
#include "protocols.h"



unsigned char RX_status = 0;	//0: No START bit detected; 1: START bit detected.

unsigned char bitCount = 0;
unsigned long demodulatedValue = 0;	//Length of 32 bits



unsigned char IR_GetStateDuration(unsigned char state){
	setTMR0(0);
    
	while(INPUT_PIN == state){}

	return getTMR0();
}


void IR_Demodulate(unsigned char fallTime, unsigned char riseTime){
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    serial_dec(fallTime);
    serial_dec(riseTime);
	//The increment frequency of TMR0 is: Fosc/(4 * prescaler)

    //Actually, this function implements only the SAMSUNG protocol
    //Change bellow in an if-else statement to add new protocols
    //e.g.  if(protocol == SAMSUNG){ ... }   else if(protocol == ... ){ ... }
    
    
    //SAMSUNG protocol
	if(RX_status == 0){
		if((fallTime >= SAMSUNG_START_BIT_LOW_MIN_DURATION && fallTime <= SAMSUNG_START_BIT_LOW_MAX_DURATION) 
                && (riseTime >= SAMSUNG_START_BIT_HIGH_MIN_DURATION && riseTime <= SAMSUNG_START_BIT_HIGH_MAX_DURATION)){
			RX_status = 1;	//Start bit detected
		}
	}
	else{	//RX_status == 1; Start bit detected
		if((fallTime >= SAMSUNG_ZERO_BIT_LOW_MIN_DURATION && fallTime <= SAMSUNG_ZERO_BIT_LOW_MAX_DURATION)
                && (riseTime >= SAMSUNG_ZERO_BIT_HIGH_MIN_DURATION && riseTime <= SAMSUNG_ZERO_BIT_HIGH_MAX_DURATION)){	//Bit 0 detected

			if(bitCount < SAMSUNG_STREAM_LENGTH - 1){
				demodulatedValue <<= 1;	//Shift to the left by 1 bit, unless the last bit is reached
			}
		}
		else if((fallTime >= SAMSUNG_ONE_BIT_LOW_MIN_DURATION && fallTime <= SAMSUNG_ONE_BIT_LOW_MAX_DURATION)
                && (riseTime >= SAMSUNG_ONE_BIT_HIGH_MIN_DURATION && riseTime <= SAMSUNG_ONE_BIT_HIGH_MAX_DURATION)){	//Bit 1 detected

			demodulatedValue |= 1;	//Logical OR with 0b0000...0001

			if(bitCount < SAMSUNG_STREAM_LENGTH - 1){
				demodulatedValue <<= 1;	//Shift to the left by 1 bit, unless the last bit is reached
			}
		}
		else{	//Some error occurred
			RX_status = 0;
		}
	}
}

unsigned long IR_Detect(void){

    if(RX_status == 0 && INPUT_PIN){	//Do NOT start until a falling edge is detected. (following the protocol)
        demodulatedValue = 0;
    }

    if(RX_status == 0){

        unsigned char fallTime = IR_GetStateDuration(LOW);
        unsigned char riseTime = IR_GetStateDuration(HIGH);

        IR_Demodulate(fallTime, riseTime);
    }

    if(RX_status == 1){	//...and not 'else'
        RX_START_DETECT_LED = HIGH;

        for(bitCount = 0 ; RX_status == 1 && bitCount < SAMSUNG_STREAM_LENGTH ; ++bitCount){
            unsigned char fallTime = IR_GetStateDuration(LOW);
            unsigned char riseTime = IR_GetStateDuration(HIGH);

            IR_Demodulate(fallTime, riseTime);
        }

        if(bitCount == SAMSUNG_STREAM_LENGTH){  //A valid signal has been captured. Now we can serial-display the captured code.
            //serial(demodulatedValue);
            RX_status = 0;
        }
    }

    RX_START_DETECT_LED = LOW;
    
    return demodulatedValue;
}



#endif	/* IR_RX_H */

