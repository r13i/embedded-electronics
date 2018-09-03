#ifndef TIMER0_H
#define	TIMER0_H

#include <xc.h>

void TMR0_Init(){
    // Helper function to setup and configure the Timer 0 (8-bit Timer)
    // The formula to calculate Timer 0 frequency is
    //  F = (Fosc/4) / (2^8 * prescaler)
    
    TMR0IF = 0;     // Timer 0 Interrupt Flag
    TMR0IE = 1;     // Timer 0 Interrupt Enable
    T0CS = 0;       // Timer 0 Clock Source (1: Set to external pin, 0: Set to internal clock, i.e. Fosc/4)
    PSA = 0;        // Pre-Scaler Assignment (1: assign to Watchdog, 0: assign to Timer 0)
    
    OPTION_REGbits.PS = 0b110;          // Prescaler set to 1:128
}

#endif	/* TIMER0_H*/

