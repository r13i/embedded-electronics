
#include <xc.h>

#include "_inc/config.h"
#include "_inc/uart.h"
#include "_inc/ir_rx.h"


extern unsigned char RX_status;

unsigned char count = 0;/////////////////////////////////////////////////////////////////////////////////////////////////
void interrupt myISR(){
	if(TMR0IE && TMR0IF){	//An overflow of TMR0 occurred. Should never get here while in IR Rx mode.
		TMR0IF = 0;

		RX_status = 0;
	}
}


void main(void) {
    SYS_Init();
    
    //TIMER0
    TMR0_Init();
    
    //UART
    UART_Init();
    
    
    while(1){
        serial(IR_Detect());
    }

    return;
}
