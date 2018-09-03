#ifndef KEYPAD_READ_H
#define	KEYPAD_READ_H

#include <xc.h>

#include "config.h"
#include "adc.h"

#include "keypad_fsm.h"


#define ZERO    0x00
#define ONE     0x01
#define TWO     0x02
#define THREE   0x03
#define FOUR    0x04
#define FIVE    0x05
#define SIX     0x06
#define SEVEN   0x07
#define EIGHT   0x08
#define NINE    0x09

#define HASH    0x0A    // The '#' on the keypad
#define STAR    0x0B    // The '*' on the keypad. (The asterix)

#define IDLE    0x0C    // When NO key is pressed



unsigned char keypad_read(void){
    // Example: Suppose that:
    // -> The ADC has a resolution of 10 bits
    // -> The keypad has 12 keys. (10 digits + '#' + '*')
    // -> To implement the keypad, we must add a state on which NO key is pressed. (IDLE state)
    // This makes 13 intervals of width: 2^10 / 13 = 78.77. The step is roughly 70.
    
    // Values below are tuned to the actual hardware. Change if needed
    
    
    if(ADC_Read_8_bits() > 245){        // No key pressed
        return IDLE;
    }
    
    
    // else (a key stroke occurred)
    unsigned char adc_result = ADC_Read_8_bits();
    
    
    // We must wait until the user releases the button
    while(ADC_Read_8_bits() < 246);
    
    
    // Then ...
    if(adc_result < 14){
        return EIGHT;
    }
    if(adc_result < 39){
        return SEVEN;
    }
    if(adc_result < 62){
        return NINE;
    }
    if(adc_result < 83){
        return FIVE;
    }
    if(adc_result < 104){
        return FOUR;
    }
    if(adc_result < 124){
        return SIX;
    }
    if(adc_result < 144){
        return ONE;
    }
    if(adc_result < 164){
        return STAR;
    }
    if(adc_result < 186){
        return TWO;
    }
    if(adc_result < 206){
        return THREE;
    }
    if(adc_result < 226){
        return ZERO;
    }
    else{
        return HASH;
    }   
}


// First declared in main.c
extern unsigned char TMR0_start_count;     // A boolean
extern unsigned char TMR0_count;   // Could get up to 16 sec with "unsigned char" and 4MHz osc and 1:256 prescaler


void keypad_access(Keypad const *k){
    
    KeypadEvent ke;
    
    // Check for a 3-sec TIMEOUT
    if(TMR0_count >= 3 * NUM_PER_SECOND){   // A timeout of 3 sec has been reached
        TMR0_start_count = 0;
        TMR0_count = 0;
        
        ke.super_.eventSignal = TIMEOUT;
        FsmTransitOnEvent((Fsm *) k, (Event *) &ke);
        
        return;
    }
    
    
    // Else
    
    ke.code = keypad_read();
    
    if(ke.code == IDLE){
        return;
    }

    // Else
    switch(ke.code){
        case ZERO:
            ke.super_.eventSignal = KEY_A_PRESSED;
            TMR0_checkTimeout();
            break;
        case ONE:
            ke.super_.eventSignal = KEY_B_PRESSED;
            TMR0_checkTimeout();
            break;
        case TWO:
            ke.super_.eventSignal = KEY_C_PRESSED;
            TMR0_checkTimeout();
            break;
        case THREE:
            ke.super_.eventSignal = KEY_D_PRESSED;
            // No need for: TMR0_checkTimeout();
            break;
            
        case HASH:
            ke.super_.eventSignal = KEY_HASH_PRESSED;
            TMR0_checkTimeout();
            break;
            
        case STAR:
            ke.super_.eventSignal = KEY_STAR_PRESSED;
            // No need for: TMR0_checkTimeout();
            break;
            
        default:
            ke.super_.eventSignal = OTHER_KEY_PRESSED;
            break;
    }

    FsmTransitOnEvent((Fsm *) k, (Event *) &ke);
    
    return;
}

#endif	/* KEYPAD_READ_H */

