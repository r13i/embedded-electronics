// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

#include <xc.h>
#include "my_PWM_16F88.h"

#define _XTAL_FREQ 8000000

unsigned char count = 0;

void interrupt my_ISR()
{
    if( TMR0IE & TMR0IF )
    {
        ++count;
        TMR0IF = 0;
    }
}

void main() {
    PWM_init( 255, 1 );
    PWM_set_duty( 0 );
    
    TRISB = PORTB = 0;
    
    TMR0 = 0;
    T0CS = PSA = 0;
    PS0 = PS1 = PS2 = 1;
    TMR0IE = GIE = 1;
    TMR0IF = 0;
    
    PWM_start();
    
    short duty_c=0;
    
    while(1)
    {
        if( count == 61 )
        {
            count = 0;
            
            RB1 = ~RB1;
            
            duty_c = ( duty_c + 128 ) % 1024;
            PWM_set_duty( duty_c );
        }
    }
    
    PWM_stop();
    return;
}