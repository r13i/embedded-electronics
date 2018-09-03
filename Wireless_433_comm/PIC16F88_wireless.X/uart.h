/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - 
*/


#ifndef UART_H
#define UART_H


#define BS  0x08    // Backspace caracter
#define ESC 0x1B    // ESC key caracter
#define EOT 0x04    // End Of Transmission (CTRL+D)



void UART_Init(){
    // Helper function to setup and configure the UART module
    // The UART protocol communicates 8-bits packets serially
    // The UART uses 2 pins to communicate (pin Rx to receive, and pin Tx to transmit)
    
    // Setup the corresponding pins
    TRISB2 = 1;       // Rx pin as input
    TRISB5 = 0;       // Tx pin as output
    
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
    
    while(! RCIF);                  // While no packet is received (reception flag is down)
    
    // Overrun Error on UART Rx
    if(RCSTAbits.OERR){
        // Resetting CREN
        CREN = 0;
        CREN = 1;
        
        return '\0';
    }
    
    return RCREG;       // Return the received packet
}

char UART_read_byte_non_blocking(){
    // Read 8-bit packet without blocking in a loop
    
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
    
    // 1st way
    /*
    unsigned char j = 0;
    while(str[j] != '\0'){
        UART_send_byte(str[j++]);
    }
    */
    
    // 2nd way
    while(*str){
        UART_send_byte(*str++);
    }
}

#endif /*UART_H*/