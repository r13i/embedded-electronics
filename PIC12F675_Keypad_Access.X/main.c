#include <xc.h>

#include "config.h"
#include "tmr0.h"
#include "adc.h"
#include "keypad_access.h"


unsigned char TMR0_start_count = 0;     // A boolean
unsigned char TMR0_count = 0;   // Could get up to 16 sec with "unsigned char" and 4MHz osc and 1:256 prescaler


Keypad k;

// For debug:
unsigned char blink_count = 0;


void interrupt ISR(){
    if(T0IE && T0IF){
        T0IF = 0;
        
        // For debug:
        ++blink_count;
        if(blink_count < 3){
            GP1 = 0;
        }
        else if(blink_count >= 6){
            blink_count = 0;
            GP1 = 1;
        }
        
        
        
        
        
        if(TMR0_start_count){
            ++TMR0_count;
        }
        
        keypad_access(&k);
    }
}


void main(void) {
    ANSELbits.ANS0 = 1;
    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 = 0;
    ANSELbits.ANS3 = 0;
    
    TRISIO = 0x01;
    GPIO = 0;
    
    TMR0_Init();
    ADC_Init();
    
    
    KeypadConstructor(&k);
    FsmTransitOnEvent((Fsm *) &k , 0);	// To transit from start state "Keypad_START()"
    
    
    while(1){
        
        // Next function is called in the interrupt ISR -see above- (on every overflow of the pre-scaled Timer0) since 
        // there is no need for high frequency processing. (Human input -Button push- is very slow, compared to the 
        // speed of this device)
        
        // keypad_access(& k);
    }
    return;
}
