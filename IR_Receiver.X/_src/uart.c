#include <xc.h>
#include <stdio.h>

#include "../_inc/uart.h"


//Actual Baud Rate is: 37500
void UART_Init(void){
    BRGH = 1;   //For high Baud Rate
    //For a Baud Rate of 37500, since formula for high Baud Rate calculation is
    // BR = Fosc/( 16*(SPBRG+1) )
    SPBRG = 19;
    
    SPEN = 1;   //Enabling Serial Port
    SYNC = 0;   //Enabling Asynchronous communication
    TXEN = 1;   //Enabling Tx
}


void serial(unsigned long value){	//To transmit via UART the demodulated value

	char buffer[25];
	sprintf(buffer, "Hex: 0x%lx", value);

	unsigned char j = 0;
	while(buffer[j] != '\0'){
		while(! TRMT){} //While the transmit buffer is not free
		TXREG = buffer[j++];
	}

	//To print New Line
	while(! TRMT){} //While the transmit buffer is not free
	TXREG = (char) 0x0D;

	while(! TRMT){} //While the transmit buffer is not free
	TXREG = (char) 0x0A;
}

// Do NOT use this because transmission speed is too slow. (Unless the input signal is slower than the transmission)
/*
void serialDebug(){	//To Debug: Used to transmit via UART some key values DURING the reception
	char buffer[30];
	sprintf(buffer, "%u %u (stat: %u)", fallTime, riseTime, RX_status);

	unsigned char j = 0;
	while(buffer[j] != '\0'){
		while(! TRMT){}
		TXREG = buffer[j++];
	}

	//To print New Line
	while(! TRMT){}
	TXREG = (char) 0x0D;

	while(! TRMT){}
	TXREG = (char) 0x0A;
}
*/
