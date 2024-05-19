#include "stm32h7xx.h"                  // Device header
#include "main.h"
#include "sys.h"
#include "pwm.h"
#include "motor.h"


int main(void)
{
	HAL_Init();
	Stm32_Clock_Init(160,5,2,4);	//…Ë÷√ ±÷”,400Mhz
	pwm();
	
	motor_left_ctl(50);
	motor_right_ctl(50);
	while(1);
		
}




	
