#include <xc.h>

#include "../_inc/pwm.h"

/*
 * PWM period     = 4 * Tosc * (PR2 + 1) * TMR2_prescaler
 * PWM duty cycle = Tosc * 10_bit_dutycycle * TMR2_prescaler
 * 
 * => D(%) = 10_bit_dutycycle / (4 * (PR2 + 1))
 */


void PWM_SetPeriod(unsigned char period){
    PR2 = period;
    return;
}

void PWM_SetDutyCycle(unsigned short dutyCycle){
    CCP1Y = dutyCycle | 0x01;
    CCP1X = (dutyCycle >> 1) | 0x01;
    CCPR1L = dutyCycle >> 2;
    return;
}

void PWM_SetDutyCycle_percent(unsigned char percentage){
    unsigned short dutyCycle = percentage * 4 * (PR2 + 1) / 100;
    
    PWM_SetDutyCycle(dutyCycle);
    return;
}

void PWM_Init(void){
    //TIMER2
    PWM_SetPeriod(0xFF);
    PWM_SetDutyCycle(0x0200);   //512 (50%)
    
    //Prescaler (1, 4, or 16)
    T2CKPS1 = T2CKPS0 = 1;
    
    TMR2ON = 1;   
    
    CCP1M3 = CCP1M2 = 1;    //Set mode to PWM
    
    return;
}