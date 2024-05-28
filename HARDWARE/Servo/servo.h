#ifndef __SERVO_H
#define __SERVO_H


void TIM4_Init(void);
void OC_servo_Init(void);
void PWM_servo_Init(void);
void servo_pwm(void);
void servo_setangle(uint8_t angle);



#endif
