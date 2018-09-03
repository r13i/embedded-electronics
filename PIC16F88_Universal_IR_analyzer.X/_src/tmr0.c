#include <xc.h>

#include "../_inc/tmr0.h"


/*
void TMR0_SetPrescaler(){
    PS2 = 1; PS1 = 0; PS0 = 1;	//Prescaler is 1:64
}
*/

void TMR0_Init(){
    
    //Enabling interrupts for TIMER0
    GIE = TMR0IE = 1;
    TMR0IF = 0;
    
    TMR0 = 0;
    T0CS = 0;
    PSA = 1;    // Prescaler NOT assigned (Check also setTMR0() function)
    
    // TMR0_SetPrescaler();     // Prescaler NOT assigned (Check also setTMR0() function)
}

unsigned char getTMR0(){
    return TMR0;
}

void setTMR0(unsigned char value){
    TMR0 = value;
    // TMR0_SetPrescaler();     // Prescaler NOT assigned
   
    return;
}