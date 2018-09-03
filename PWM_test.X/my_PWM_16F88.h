#ifndef MY_PWM_16F88_H
#define	MY_PWM_16F88_H

#include <xc.h>

//#define _XTAL_FREQ 8000000  ////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int PWM_freq = 0;

void PWM_init( char pr2_val, char tmr2_prescal )
{
    //tmr2_prescaler must be 1, 4, or 16
    
    //Setting the Period
    PR2 = pr2_val;
    switch( tmr2_prescal )
    {
        case 1:
            T2CKPS1 = T2CKPS0 = 0;
            break;
        case 4:
            T2CKPS1 = 0;    T2CKPS0 = 1;
            break;
        case 16:
            T2CKPS1 = T2CKPS0 = 1;
            break;
    }
    
    //PWM_freq = _XTAL_FREQ / ( 4*(pr2_val+1)*tmr2_prescal );
    
    CCP1M3 = CCP1M2 = 1;    //Setting the PWM mode
}

void PWM_set_duty( short duty_c )
{
    //duty_c must be 10-bit length
    CCP1Y = duty_c % 2;
    CCP1X = ( duty_c/2 ) % 2;
    CCPR1L = duty_c / 4;
}

void PWM_start()
{
    TMR2ON = 1;
}

void PWM_stop()
{
    TMR2 = 0;
}

#endif