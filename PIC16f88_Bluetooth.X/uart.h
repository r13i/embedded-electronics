#ifndef UART_H
#define UART_H

#include "config.h"



void UART_Init(){
    TRISBbits.TRISB2 = 1;		// Rx pin as input
    TRISBbits.TRISB5 = 0;		// Tx pin as output
    
    
    BRGH = 1;
    SPBRG = 51;
    
    SYNC = 0;
    SPEN = 1;
    
    // Tx
    TX9 = 0;
    TXEN = 1;
    
    // Rx
    RX9 = 0;
    CREN = 1;
}

void UART_send_byte(unsigned char single_byte){
    while(! TRMT);
    TXREG = single_byte;
}

char UART_read_byte(){
    
    while(! RCIF);
    
    // Overrun Error on UART Rx
    if(RCSTAbits.OERR){
        // Resetting CREN
        CREN = 0;
        CREN = 1;
        
        return '\0';
    }
    
    return RCREG;
}

void UART_send_string(char* str){
    /*
    unsigned char j = 0;
    while(str[j] != '\0'){
        UART_send_byte(str[j++]);
    }
    */
    
    while(*str){
        UART_send_byte(*str++);
    }
}


#endif /*UART_H*/