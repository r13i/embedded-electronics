
#include <xc.h>

#include "_inc/config.h"
#include "_inc/uart.h"
#include "_inc/ir_rx.h"
#include "_inc/pwm.h"


void interrupt myISR(){
	if(TMR0IE && TMR0IF){	//An overflow of TMR0 occurred. Should never get here while in IR Rx mode.
		TMR0IF = 0;

		RX_status = 0;
	}
}


void main(void) {
    ANSEL = 0;
    TRISA = 0;
    TRISB = 0b00001000;	//Input is INPUT_PIN, RB0 is PWM output
    
    PORTA = 0b00000100;
    PORTB = 0b00001000;	//INPUT_PIN starts with a HIGH value
    
    //TIMER0
    TMR0_Init();
    
    //UART
    //UART_Init();
    
    //PWM
    PWM_Init();

    unsigned short dutyCycle = 0x0200;  //512 = 2^10 / 2
    while(1){
        unsigned long val = IR_Detect();
        
        if(val == SAMSUNG.UP){
            DISPLAY_LED = HIGH;
            
            if(dutyCycle < 974){    //1023 - 50 + 1, since 1023 is the MAXIMUM duty cycle in 10-bit resolution
                dutyCycle += 50;
                
                PWM_SetDutyCycle(dutyCycle);
            }
        }
        else if(val == SAMSUNG.DOWN){
            DISPLAY_LED = LOW;
            
            if(dutyCycle > 49){ //Since 0 is the MINIMUM duty cycle
                dutyCycle -= 50;
                
                PWM_SetDutyCycle(dutyCycle);
            }
        }
    }

    return;
}
