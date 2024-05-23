#include "stm32h7xx.h"                  // Device header
#include "main.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"
#include "motor.h"
#include "HC-SR04.h"

float Distance = 0;

int main(void)
{

	HAL_Init();
	Stm32_Clock_Init(160,5,2,4);	//ÉèÖÃÊ±ÖÓ,400Mhz
	delay_init(400);
	uart_init(115200);
	pwm();
	HC_SR04_GPIO_Init();
	HC_SR04_TIM7_Init();
	HC_SR04_TIM4_Init();
	led_init();

	
	motor_left_ctl(50);
	motor_right_ctl(50);
	while(1)
	{
		//HC_SR04_Start();
		//led_on();
		
		//HC_SR04_GetDistance();
		if(Distance > 8)
		{
			led_off();
		}
		else
		{
			led_on();
		}
		//Distance = HC_SR04_GetDistance();
		printf("Distance:%f cm\r\n",Distance);
		//delay_ms(1000);
		//led_off();
		
	
	}
		
}




	
