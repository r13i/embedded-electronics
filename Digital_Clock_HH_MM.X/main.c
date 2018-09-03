/*
 * File:   main.c
 * Author: USER
 *
 * Created on 28 janvier 2017, 09:26
 */
/*
 * The 7-seg display must be common-anode
 * Actual time must be set from this firmware (Oops, lack of push-buttons ...)
 */

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
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

#include <xc.h>

unsigned char count=0;

void seg_disp( unsigned char N )
{
    //N is the digit to display, and thus must be between 0 and 9
    
    char seg[16] = { 0b00111111, 0b00000110, 0b01011011,
    0b01001111, 0b01100110, 0b01101101, 0b01111100, 0b00000111, 0b01111111,
    0b01100111/*, 0b01110111, 0b01111100, 0b01011000, 0b01011110, 0b01111001,
    0b01110001*/ };

    PORTB = ~seg[N];    //The 7-seg display is common-anode
}

void digit_disp(void)
{
    static unsigned char i=0;
    static unsigned char SS=0;
    static unsigned char MM=0;
    static unsigned char HH=0;
    
    if( count==244 )    //The count reached 1 second, for 8 MHz crystal
    {
        ++SS;
        count=0;
            
        if( SS==60 ){ ++MM; SS=0; }
        if( MM==60 ){ ++HH; MM=0; }
        if( HH==24 ){ HH=0; }
    }
    
    if( i==0 )  //First digit
    {
        RA0 = 1;
        RA1 = RA2 = RA3 = 0;
        seg_disp( MM % 10 );
        i = 1;
    }
    else if( i==1 ) //Second digit
    {
        RA1 = 1;
        RA0 = RA2 = RA3 = 0;
        seg_disp( (char)MM / 10 );
        i = 2;
    }
    else if( i==2 )
    {
        RA2 = 1;
        RA0 = RA1 = RA3 = 0;
        seg_disp( HH % 10 );
        
        RA4 = ( count<122 )? 0 : 1; //For double-dot blinking
        
        i = 3;
    }
    else
    {
        RA3 = 1;
        RA0 = RA1 = RA2 = 0;
        seg_disp( (char)HH / 10 );
        i = 0;
    }
}

void interrupt my_ISR()
{
    if( TMR0IE && TMR0IF )
    {
        ++count;
        digit_disp();
        
        TMR0IF = 0;
    }
}

void main(void) {
    ANSEL = 0;
    TRISA = TRISB = 0;
    PORTA = 0x01;
    PORTB = 0xBF;
    
    OPTION_REG = 0b11010100;        //Prescaler 1:32 assigned to TMR0
    INTCON = 0b11100000;
    
    while(1){
    }
    
    return;
}
