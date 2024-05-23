#include "stm32h7xx.h"                  // Device header
#include "pwm.h"

void motor_left_ctl(int8_t speed)
{
	if(speed>=0)
	{
		TIM2->CCR1 = 0;
		TIM2->CCR2 =speed;	
	}
	if(speed<0)
	{
		TIM2->CCR1 = -speed;
		TIM2->CCR2 =0;	
	}

}


void motor_right_ctl(int8_t speed)
{
	if(speed>=0)
	{
		TIM2->CCR3 = 0;
		TIM2->CCR4 =speed;	
	}
	if(speed<0)
	{
		TIM2->CCR3 = -speed;
		TIM2->CCR4 =0;	
	}

}

void left(void)
{
	motor_left_ctl(80);
	motor_right_ctl(80);
}


void right(void)
{
	motor_left_ctl(-80);
	motor_right_ctl(-80);
}

void forward(void)
{
	motor_left_ctl(80);
	motor_right_ctl(-80);
}

void backward(void)
{
	motor_left_ctl(-80);
	motor_right_ctl(80);
}

void rotation(void)
{
	motor_left_ctl(60);
	motor_right_ctl(80);

}









