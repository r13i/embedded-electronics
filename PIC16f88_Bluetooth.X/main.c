#include <xc.h>
#include <stdio.h>

#include "config.h"
#include "uart.h"
#include "adc.h"


#define ONE_SEC 61      // Num ot TIMER0 overflows to get 1 sec
#define SEND_PERIOD 1   // Sec

#define N_SENSORS 2
unsigned char SENSOR_CHANNELS[N_SENSORS] = {0, 1};
char* SENSOR_TYPES[N_SENSORS] = {(char*) "Light", (char*) "Gas"};


void Syst_Init(){
    ANSEL = 0;
    TRISA = TRISB = 0;
    PORTA = PORTB = 0;
    RA2 = 1;
    RA3 = 1;
    
    GIE = PEIE = 1;
}

void TMR0_Init(){
    TMR0IF = 0;
    TMR0IE = 1;
    T0CS = 0;
    PSA = 0;
    
    OPTION_REGbits.PS = 0b110;
}


unsigned short adc_uart_count = 0;

void interrupt ISR(){
    if(TMR0IE && TMR0IF){
        TMR0IF = 0;
        ++adc_uart_count;
        
        
        if((2 * adc_uart_count) % ONE_SEC == 0){    // Toggle each half second
            RA2 = ~RA2;
        }

        if(adc_uart_count >= ONE_SEC * SEND_PERIOD){
            adc_uart_count = 0;
            
            unsigned char j = 0;
            for(j = 0; j < N_SENSORS; ++j){
                char buffer[30];
                sprintf(buffer, "%s: %lu / 100", SENSOR_TYPES[j], (unsigned long) ADC_Read(SENSOR_CHANNELS[j]) * 100 / 1024);
                UART_send_string(buffer);
                UART_send_byte(0x0A);
                UART_send_byte(0x0D);   
            }
            
            UART_send_byte(0x0A);
            UART_send_byte(0x0D);
        }
    }
}


void main(void) {
    
    Syst_Init();
    TMR0_Init();
    UART_Init();
    ADC_Init();
    
    
    while(1){
        char rx_read = UART_read_byte();
        
        if(rx_read != '\0'){
            if(rx_read == 't'){
                RA3 = ~RA3;
            }
            else if(rx_read == '1'){
                RA3 = 1;
            }
            else if(rx_read == '0'){
                RA3 = 0;
            }
        }
    }
    
    return;
}
