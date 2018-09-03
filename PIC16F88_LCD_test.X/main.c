
#include <xc.h>

#include "config.h"
#include "lcd.h"


#define ONE_SEC 183      // Num ot TIMER0 overflows to get 1 sec

void Syst_Init(){
    ANSEL = 0;
    TRISA = TRISB = 0;
    PORTA = PORTB = 0;
    
    GIE = PEIE = 1;
}

void TMR0_Init(){
    TMR0IF = 0;
    TMR0IE = 1;
    T0CS = 0;
    PSA = 0;
    
    OPTION_REGbits.PS = 0b110;
}

unsigned char timerCount = 0;
void interrupt ISR() {
    if(TMR0IE && TMR0IF){
        TMR0IF = 0;
        ++timerCount;
        
        if (timerCount >= ONE_SEC) {
            timerCount = 0;
            
            //
        }
    }

}


void main() {
    Syst_Init();
    TMR0_Init();
    LCD_Init();

    while (1) {
        LCD_clear();
        LCD_set_cursor(1, 1);
        LCD_write_string("LCD Library for");

        LCD_set_cursor(2, 1);
        LCD_write_string("MPLAB XC8");
        __delay_ms(2000);

        LCD_set_cursor(3, 1);
        LCD_write_string("Developed By");
        LCD_set_cursor(4, 1);
        LCD_write_string("electroSome");
        __delay_ms(2000);

        LCD_clear();
        LCD_set_cursor(1, 1);
        LCD_write_string("www.electroSome.com");

        unsigned char j;
        for(j = 0; j < 20; j++) {
            __delay_ms(300);
            LCD_shift_left();
        }

        for(j = 0; j < 20; j++) {
            __delay_ms(300);
            LCD_shift_right();
        }

        LCD_clear();
        LCD_set_cursor(2, 1);
        LCD_write_char('e');
        LCD_write_char('S');
        __delay_ms(2000);
    }
}