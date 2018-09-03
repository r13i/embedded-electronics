/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - 
*/


#include <xc.h>
#include <stdio.h>      // For "sprintf"

#include "config.h"
#include "virtualwire.h"
#include "uart.h"


// VW_MAX_MESSAGE_LEN is modified
uint8_t text[VW_MAX_MESSAGE_LEN];

void interrupt global_isr(void){
	if(TMR0IF)
		vw_isr_tmr0();
}

void main(void){
    TRISB = 0;
    PORTB = 0;
    
	uint16_t i;
	
    UART_Init();        // Actually at 9600 bauds
    
    // VW_MAX_MESSAGE_LEN is modified
	vw_setup(200);
    // vw_set_rx_inverted();    // Invert if the RF receivers inverts the data


	UART_send_string((char *) "PIC Receiver Demo\n");
    UART_send_byte(0xD);
    UART_send_byte(0xA);
    
    __delay_ms(1000);
    
	UART_send_string((char *) "PIC Receiver Demo\n");
    UART_send_byte(0xD);
    UART_send_byte(0xA);
    
    __delay_ms(1000);
    
	UART_send_string((char *) "PIC Receiver Demo\n");
    UART_send_byte(0xD);
    UART_send_byte(0xA);

	vw_rx_start();

	while(1){
		if (vw_have_message()){
            
            // VW_MAX_MESSAGE_LEN is modified
			uint8_t len = VW_MAX_MESSAGE_LEN;

			if (vw_recv(text, &len)){
                
                char buffer[30];
                sprintf(buffer, "Light percentage: %s", text);
                
                UART_send_string((char *) buffer);

				// for (i = 0; i < len; i++){
                //     UART_send_byte(text[i]);
                // }

				UART_send_byte(0xD);
				UART_send_byte(0xA);
			}
		}
	}
	
}
