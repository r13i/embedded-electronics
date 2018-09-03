/*
 * File:   main.c
 * Author: USER
 *
 * Created on 26 janvier 2017, 20:47
 */
/*  
 * The 7-segment display used is common-anode 
 */

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

#include <xc.h>

#define _XTAL_FREQ 8000000

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

void digit_disp( void )
{
    static unsigned char i=0;
    static unsigned char SS=0;
    static unsigned char MM=0;
    
    if( count==122 )    //The count reached 1 second, for 8 MHz crystal
    {
        ++SS;
        count=0;
            
        if( SS==60 ){ ++MM; SS=0; }
        if( MM==60 ){ MM=0; }
    }
    
    if( i==0 )  //First digit
    {
        RA0 = 1;
        RA1 = RA2 = RA3 = 0;
        seg_disp( SS % 10 );
        i = 1;
    }
    else if( i==1 ) //Second digit
    {
        RA1 = 1;
        RA0 = RA2 = RA3 = 0;
        seg_disp( (char)SS / 10 );
        i = 2;
    }
    else if( i==2 )
    {
        RA2 = 1;
        RA0 = RA1 = RA3 = 0;
        seg_disp( MM % 10 );
        i = 3;
    }
    else
    {
        RA3 = 1;
        RA0 = RA1 = RA2 = 0;
        seg_disp( (char)MM / 10 );
        i = 0;
    }
}

void interrupt my_ISR()
{
    if( TMR0IE && TMR0IF )
    {
        TMR0IF = 0;

        ++count;
        digit_disp();
    }
}

void main(void) {
    ANSEL = 0;  //All I/O ports are digital
    TRISA = TRISB = 0;  //All ports are outputs
    PORTA = 0x01;
    PORTB = 0b10111111;     //To show a horizontal bar on the 7-seg display. RB7 not used
    
    OPTION_REG = 0b10000101;
    INTCON = 0b11100000;
    
    while(1)
    {
    }
    
    return;
}