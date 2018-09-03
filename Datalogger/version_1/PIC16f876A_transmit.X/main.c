/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - mohamed_amir_alaa.belmekki@g.enp.edu.dz 
*/

#include <xc.h>
#include <stdio.h>      // for sprintf()

#include "config.h"
#include "timer0.h"
#include "uart.h"
#include "adc.h"


/*************************************************************************************************/
#define ONE_SEC 61      // Num of TIMER0 overflows to get 1 sec for actual crystal frequency
#define SEND_PERIOD 1   // Seconds. Send via UART each SEND_PERIOD seconds


/*************************************************************************************************/
// Set Gas threshold
#define GAS_THRESHOLD 511       // Format to fit the range [0 - 1024] of the 10-bit ADC

/*************************************************************************************************/
#define N_SENSORS 2         // Number of sensors in this application

// Setup sensor channels (Must fit the "for" loop in interrupt ISR below. If any doubt, leave as is)
#define LIGHT_SENSOR 0
#define GAS_SENSOR 1

unsigned char SENSOR_CHANNELS[N_SENSORS] = {LIGHT_SENSOR, GAS_SENSOR};
char* SENSOR_TYPES[N_SENSORS]            = {(char*) "Light", (char*) "Gas"};


/*************************************************************************************************/
unsigned char alarm_on = 0;        // Boolean specifying whether the alarm is ON or OFF
unsigned short timer0_count = 0;    // Counter for the Timer 0 overflows



/*************************************************************************************************/
void Syst_Init(){
    // Helper function to setup the general functions of this microcontroller
    
    // Setup PORTA, PORTB, and PORTC as outputs (logical, not analog)
    TRISA = TRISB = TRISC = 0;
    
    // Setup logic level to LOW
    PORTA = PORTB = PORTC = 0;

    // Enable INTERRUPTS
    // GIE  : General Interrupt Enable
    // PEIE : Peripheral Interrupt Enable
    GIE = PEIE = 1;
}


/*************************************************************************************************/
// Interrupt Service Routine: Handler for the interrupts
void interrupt ISR(){
    
    if(TMR0IE && TMR0IF){       // If a Timer 0 overflow occurs, the flag TMR0IF rises
        
        TMR0IF = 0;         // Set down the flag
        ++timer0_count;     // Increment the counter
        
        // Blink the alarm
        if(alarm_on && (timer0_count << 1) % (unsigned char) (ONE_SEC / 2) == 0){
            ALARM_PIN = ~ALARM_PIN;
        }

        // Send sensors data via UART each SEND_PERIOD seconds
        if(timer0_count >= ONE_SEC * SEND_PERIOD){
            
            timer0_count = 0;       // Reset the counter once the period reached
            
            // Send data about each sensor
            unsigned char j = 0;
            for(j = 0; j < N_SENSORS; ++j){
                char buffer[20];    // A string buffer to hold the data
                sprintf(buffer, "%s: %lu / 100", SENSOR_TYPES[j], (unsigned long) ADC_Read(SENSOR_CHANNELS[j]) * 100 / 1024);
                
                // Send the string via UART to RF module, which will send them wirelessly
                UART_send_string(buffer);
                
                // new line + carriage return (NL + CR)
                UART_send_byte(0x0A);
                UART_send_byte(0x0D);   
            }
            
            // new line + carriage return (NL + CR)
            UART_send_byte(0x0A);
            UART_send_byte(0x0D);
        }
    }
}


/*************************************************************************************************/
void main(void) {
    
    Syst_Init();
    TMR0_Init();   
    UART_Init();
    ADC_Init();
    
    ALARM_PIN = 0;      // Set the pin to LOW
    
    
    unsigned char enable_alarm = 1;
    unsigned char is_above_threshold = 0;
    
    while(1){     
        
        // Detect if gas level is above threshold
        // From ADC read
        is_above_threshold = (ADC_Read((unsigned char) GAS_SENSOR) >= GAS_THRESHOLD)? 1 : 0;//if above threshold: 1 else 0
        
        // From Gas sensor's digital output (1: if gas level above threshold, 0: otherwise)
        // is_above_threshold = (GAS_SENSOR_DIGITAL_INPUT == 0) ? 0 : 1;
                
        
        
        // Below is the logic implemented to build the gas alarm
        
        if(enable_alarm && is_above_threshold){
            
            if(! alarm_on){                
                UART_send_string((char *) "!!!!! GAS ALARM !!!!!");
                
                UART_send_byte(0x0D);
                UART_send_byte(0x0A);
                
                UART_send_byte(0x0D);
                UART_send_byte(0x0A);
            }
            

            alarm_on = 1;
        }
        else{
            alarm_on = 0;
            ALARM_PIN = 0;
        }
        
        if(! enable_alarm && !is_above_threshold){
            enable_alarm = 1;
        }
        
        
        // See if user wants to shut down the alarm
        char rx_read = UART_read_byte();
        
        if(rx_read != '\0'){    // If no transmission error
            if(rx_read == '1'){
                enable_alarm = 1;
                alarm_on = 1;
                
                UART_send_string((char *) "!!!!! GAS ALARM !!!!!");
                UART_send_byte(0x0D);
                UART_send_byte(0x0A);
            }
            
            else if(rx_read == '0'){
                enable_alarm = 0;
                alarm_on = 0;
                
                ALARM_PIN = 0;
            }
        }
    }
    
    return;
}
