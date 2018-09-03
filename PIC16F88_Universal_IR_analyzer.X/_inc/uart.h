#ifndef UART_H
#define	UART_H


//Actual Baud Rate is: 37500
void UART_Init(void);


void serial(unsigned long value);	//To transmit via UART the demodulated value
void serial_dec(unsigned long value);	//To transmit via UART the demodulated value

// Do NOT use this because transmission speed is too slow. (Unless the input signal is slower than the transmission)
/*
void serialDebug();	//To Debug: Used to transmit via UART some key values
*/


#endif	/* UART_H */

