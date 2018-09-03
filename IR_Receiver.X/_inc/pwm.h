#ifndef PWM_H
#define	PWM_H


/*
 * PWM period     = 4 * Tosc * (PR2 + 1) * TMR2_prescaler
 * PWM duty cycle = Tosc * 10_bit_dutycycle * TMR2_prescaler
 * 
 * => D(%) = 10_bit_dutycycle / (4 * (PR2 + 1))
 */

void PWM_SetPeriod(unsigned char period);

void PWM_SetDutyCycle(unsigned short dutyCycle);

void PWM_SetDutyCycle_percent(unsigned char percentage);

void PWM_Init(void);



#endif	/* PWM_H */

