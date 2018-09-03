/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - mohamed_amir_alaa.belmekki@g.enp.edu.dz 
*/

#include <xc.h>
#include <stdio.h>      // For sprintf()

#include "config.h"
#include "uart.h"


/*************************************************************************************************/
void Syst_Init(){
    // Helper function to setup the general functions of this microcontroller
    
    // Setup PORTA and PORTB as outputs (logical, not analog)
    TRISA = TRISB = 0;
    
    // Setup logic level to LOW
    PORTA = PORTB = 0;

    // Enable INTERRUPTS
    // GIE  : General Interrupt Enable
    // PEIE : Peripheral Interrupt Enable
    GIE = PEIE = 1;
}

void main(){
    
    Syst_Init();
    UART_Init();
    
    char* str = NULL;
    char buffer[30];
    
    while(1){
        /*
        while(UART_read_string(str, 20) == 0);
        
        sprintf(buffer, "PIC16F88 received from PIC16F876A : %s", str);
        UART_send_string(buffer);
        */
        
        char ch = '\0';
        do {
            ch = UART_read_byte();
        } while (ch == '\0');
        
        UART_send_byte(ch);
        
    }
}
