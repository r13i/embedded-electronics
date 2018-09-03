#ifndef TMR0_H
#define TMR0_H

#define NUM_PER_SECOND 15  // Formula: F_osc / (4 * TMR0_LENGTH_IS_256 * PRESCALER)    // Actual application: 4 MHz / (4 * 256 * 256) = 15.26

extern unsigned char TMR0_start_count;     // A boolean
extern unsigned char TMR0_count;   // Could get up to 16 sec with "unsigned char" and 4MHz osc and 1:256 prescaler

void TMR0_Init(){
    T0IF = 0;
    GIE = T0IE = 1;
    
    T0CS = 0;
    PSA = 0;
    PS2 = 1; PS1 = 1; PS0 = 1;
}

void TMR0_setTMR0(unsigned char val){
    TMR0 = val;
    PS2 = 1; PS1 = 1; PS0 = 1;  // Re-assigning prescaler values. (Mandatory)
}

void TMR0_checkTimeout(){
    TMR0_count = 0;
    TMR0_setTMR0(0);
    TMR0_start_count = 1;
    
    // See the interrupt ISR in main.c and keypad_access()
}

#endif /*TMR0_H*/