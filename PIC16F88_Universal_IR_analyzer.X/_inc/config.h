/*
 * Change bellow according to the PIC microcontroller you are using.
 * 
 * Actual: PIC 16F88
*/

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>


//##############################################################################
// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

//##############################################################################


// #define _XTAL_FREQ 125000    // 125 kHz

#define INPUT_PIN RB3
#define RX_START_DETECT_LED RA3
#define DISPLAY_LED RA2


#define HIGH 1
#define LOW 0



void SYS_Init(void){
    ANSEL = 0;
    TRISA = 0;
    TRISB = 0b00001000;	//Input is INPUT_PIN, RB0 is PWM output
    
    PORTA = 0b00000100;
    PORTB = 0b00001000;	//INPUT_PIN starts with a HIGH value


    OSCTUNE = 0x00;
    OSCCONbits.IRCF = 1;    // Freq set to 125 kHz
}

#endif	/* CONFIG_H */

