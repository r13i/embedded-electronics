
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

#include <xc.h>

#define _XTAL_FREQ 12000000
//In order to generate an good quality, audible sound with freq up to 
//11.7KHz, an 12MHz external oscillator, associated to TMR0, with a prescaler of 1:1
//The maximum sound duration generated at once is 366 sec

unsigned short short_count=0; //For sound freq generation
unsigned long long_count=0;   //For sound duration
void interrupt my_ISR()
{
    if( TMR0IE && TMR0IF )
    {
        ++short_count;
        ++long_count;
        TMR0 = 128;
        TMR0IF = 0;
    }
}

void main(void) {
    T0CS = 0;   //Clock source on Fosc/4
    PSA = 1;    //Prescaler assigned to WDT, i.e. TMR0 receives a 1:1 prescaler
    
    GIE = TMR0IE = 1;   //Enabling interrupts
    TMR0IF = 0; //Clearing the interrupt flag
    TMR0 = 128;
    
    ANSEL = 0;
    TRISA = TRISB = 0;
    PORTA = PORTB = 0;

    while(1)
    {
        while( long_count < 5859 ){
	if( (1000 * short_count) >= 17776 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 21139 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 19953 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 21139 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 26634 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 26634 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;


while( long_count < 2930 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 17776 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 19953 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 6598 ){
	if( (1000 * short_count) >= 21139 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 19953 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 17776 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 26634 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 26634 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 26634 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 21139 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 22396 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 6598 ){
	if( (1000 * short_count) >= 19953 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 16778 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 5859 ){
	if( (1000 * short_count) >= 13317 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 14948 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 2930 ){
	if( (1000 * short_count) >= 16778 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;

while( long_count < 6598 ){
	if( (1000 * short_count) >= 17776 ){
			RA1 = ~RA1;	short_count = 0;
	}
}
long_count = 0;



    }
    return;
}
