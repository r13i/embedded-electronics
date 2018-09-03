/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - mohamed_amir_alaa.belmekki@g.enp.edu.dz 
*/

#ifndef UART_H
#define UART_H


#include "config.h"     // To get _XTAL_FREQ . Otherwise, just #define it


#define BS  0x08    // Backspace caracter
#define ESC 0x1B    // ESC key caracter
#define EOT 0x04    // End Of Transmission (CTRL+D)



void UART_Init(){
    // Helper function to setup and configure the UART module
    // The UART protocol communicates 8-bits packets serially
    // The UART uses 2 pins to communicate (pin Rx to receive, and pin Tx to transmit)
    
    // Setup the corresponding pins
    TRISB5 = 0;       // Tx pin as output
    TRISB2 = 1;       // Rx pin as input
    
    // Set Baud Rate to 9600
    BRGH = 1;
    SPBRG = 77;

    
    SYNC = 0;       // Setup UART to Asynchronous
    SPEN = 1;       // Enable the serial port
    
    // Tx
    TX9 = 0;        // Disable 9-bit transmission
    TXEN = 1;       // Enable transmission
    
    // Rx
    RX9 = 0;        // Disable 9-bit reception
    CREN = 1;       // Enable continuous reception
}

void UART_send_byte(unsigned char single_byte){
    // Send 8-bit packet
    
    while(! TRMT);          // While not done with previous packet
    TXREG = single_byte;    // Put the packet in the buffer register of the transmission module. It will be sent automatically.
}

char UART_read_byte(){
    // Read 8-bit packet
    
    // while(! RCIF);                  // While no packet is received (reception flag is down)
    if(! RCIF){
    	return '\0';
    }
    
    // Overrun Error on UART Rx
    if(RCSTAbits.OERR){
        // Resetting CREN
        CREN = 0;
        CREN = 1;
        
        return '\0';
    }
    
    return RCREG;       // Return the received packet
}

void UART_send_string(char* str){
    // Send a whole string
    
    // 1st method
    /*
    unsigned char j = 0;
    while(str[j] != '\0'){
        UART_send_byte(str[j++]);
    }
    */
    
    // 2nd method
    while(*str){
        UART_send_byte(*str++);
    }
}


unsigned char UART_read_string(char *str, unsigned int len)
{
    unsigned char index, ch;

    ch = UART_read_byte();
    if(ch == '\0'){
        return 0;
    }

    index = 0;
    while (ch == '\n' || ch == '\r' || ch == '\0') {
        ch = UART_read_byte();
    }
    
    while (ch != EOT && ch != '\r' && ch != '\n' && ch != '\0' && index < len) {
        str[index++] = ch;
        ch = UART_read_byte();
    }
    
    str[index] = '\0';
    
    return 1;
}



#endif /*UART_H*/