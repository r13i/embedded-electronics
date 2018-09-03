/*
*   Authors : ACHOURI Ahmed Redouane - ahmed_redouane.achouri@g.enp.edu.dz
*             BELMEKKI Amir Alaa     - 
*/


#include <xc.h>
#include <stdlib.h>     // For "atoi"
#include <stdio.h>      // For "sprintf"
#include <string.h>     // For parsing the received message

#include "config.h"
#include "virtualwire.h"
#include "lcd.h"

#define SENSOR_ID_0 0
#define SENSOR_ID_1 1

// VW_MAX_MESSAGE_LEN is modified
uint8_t text[VW_MAX_MESSAGE_LEN];

volatile char clockBuffer[15];
volatile char adcBuffer_0[20] = "";
volatile char adcBuffer_1[20] = "";

volatile unsigned char timerCounter = 0;
volatile unsigned char HH = 0;
volatile unsigned char MM = 0;
volatile unsigned char SS = 0;


void parse_id_value (char * str, char ** id, char ** value) {
    // Received message contains "SENSOR_ID,VALUE" (Notice the comma separator)
    (* id) = strtok(str, (char *) ",");      // Get first token
    (* value) = strtok(NULL, (char *) ",");  // Get second token. The NULL pointer is used to make the function continue.
}

void SYST_Init () {    
    ADCON1 = 0x06;      // Set all entries to DIGITAL (especially Rx and Tx for "virtualwire". See virtualwire.h)
    TRISA = 0;
    TRISB = 0;
    
    PORTA = 0;
    PORTB = 0;
    
    GIE = PEIE = 1;
}

void TMR1_Init() {
    TMR1IF = 0;
    TMR1IE = 1;
    
    T1CONbits.T1CKPS = 1;       // Set prescaler to 1:2
    TMR1CS = 0;
    TMR1ON = 1;
}

void interrupt global_isr(void){
	if(TMR0IF)
		vw_isr_tmr0();
    
    else if (TMR1IE && TMR1IF) {
        TMR1IF = 0;
        timerCounter++;
        
        if (timerCounter >= 23) {
            timerCounter = 0;

            SS++;
            if (SS > 59) { SS = 0; MM++; }
            if (MM > 59) { MM = 0; HH++; }
            if (HH > 59) { HH = 0; }

            sprintf((char *) clockBuffer, "%02u : %02u : %02u", HH, MM, SS);
        }
    }
}

void main(void){

    SYST_Init();
    TMR1_Init();
    LCD_Init();
    
	vw_setup(200);              // VW_MAX_MESSAGE_LEN is modified
    // vw_set_rx_inverted();    // Invert if the RF receiver inverts the data
	vw_rx_start();

	while(1){
		if (vw_have_message()){
			uint8_t len = VW_MAX_MESSAGE_LEN;   // VW_MAX_MESSAGE_LEN is modified

			if (vw_recv(text, &len)){
                char * id;
                char * value;
                parse_id_value (text, &id, &value);
                
                int int_id = atoi(id);
                if (int_id == SENSOR_ID_0) {
                    sprintf((char *) adcBuffer_0, "light: %s %%", value);
                }
                else if (int_id == SENSOR_ID_1) {
                    sprintf((char *) adcBuffer_1, "voltage: %s %%", value);
                }
			}
		}

        // LCD_clear();
        LCD_set_cursor(1, 2);
        LCD_write_string((char *) "*super*datalogger*");
        LCD_set_cursor(2, 5);
        LCD_write_string((char *) clockBuffer);
        LCD_set_cursor(3, 1);
        LCD_write_string((char *) adcBuffer_0);
        LCD_set_cursor(4, 1);
        LCD_write_string((char *) adcBuffer_1);
	}
}
