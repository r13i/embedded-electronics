#ifndef CONFIG_H
#define	CONFIG_H


// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


#define _XTAL_FREQ 4000000      // Actual freq of the internal Oscillator


#define ADC_INPUT GP0

// If you change below, you must also change the GPIO registers accordingly
#define SIGNAL_START_RECOGNITION GP4   // These signals (further implemented in keypad_fsm.h to be a few millisec long) are used to start tasks
#define SIGNAL_START_UPDATE GP5   // These tasks (in this project) are accomplished by the Raspberry Pi


#endif	/* CONFIG_H */

