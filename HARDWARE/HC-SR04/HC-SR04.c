#include "usart.h"
#include "stm32h7xx.h"                  // Device header
#include "delay.h"


#define Trig GPIO_PIN_1
#define Echo GPIO_PIN_2

//int echo_flag , echo_end;
float temp , time;
int is_high;

TIM_HandleTypeDef TIM7_HandleType;
TIM_HandleTypeDef TIM4_HandleType;

extern float Distance;
//float Distance;

void HC_SR04_TIM7_Init(void)
{
	__HAL_RCC_TIM7_CLK_ENABLE();
	
	TIM7_HandleType.Instance = TIM7;
	TIM7_HandleType.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM7_HandleType.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM7_HandleType.Init.Period = 10000;
	TIM7_HandleType.Init.Prescaler = 10000-1;
	TIM7_HandleType.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&TIM7_HandleType);
	
	TIM_ClockConfigTypeDef TIM7_ClockConfigType;
    TIM7_ClockConfigType.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&TIM7_HandleType, &TIM7_ClockConfigType);


}

// void HC_SR04_TIM4_Init(void)
//{
//    __HAL_RCC_TIM4_CLK_ENABLE();
//	
//    TIM4_HandleType.Instance = TIM4;
//	TIM4_HandleType.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    TIM4_HandleType.Init.Prescaler = 5000-1;
//    TIM4_HandleType.Init.CounterMode = TIM_COUNTERMODE_UP;
//    TIM4_HandleType.Init.Period = 5000-1;
//    TIM4_HandleType.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//	
//	HAL_TIM_Base_Init(&TIM4_HandleType);
//	
//	TIM_ClockConfigTypeDef TIM4_ClockConfigType;
//    TIM4_ClockConfigType.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//    HAL_TIM_ConfigClockSource(&TIM4_HandleType, &TIM4_ClockConfigType);
//	
//	HAL_TIM_Base_Start_IT(&TIM4_HandleType);
//}


void HC_SR04_GPIO_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIOC_Init;
	
    GPIOC_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOC_Init.Pin = Trig;
    GPIOC_Init.Pull = GPIO_NOPULL;
    GPIOC_Init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIOC_Init);

    //GPIOC_Init.Mode = GPIO_MODE_IT_RISING;
	GPIOC_Init.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIOC_Init.Pin = Echo;
    GPIOC_Init.Pull = GPIO_NOPULL;
    GPIOC_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIOC_Init);
	
	//HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(EXTI2_IRQn,1,0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	
//	HAL_NVIC_SetPriority(TIM4_IRQn,2,0);
//	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}


//外部中断开关定时器计数器，记录超声波时间
void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(Echo);

}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 if(GPIO_Pin == Echo)
	{
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_Pin) == 1)
		{
			__HAL_TIM_SET_COUNTER(&TIM7_HandleType,0);
			HAL_TIM_Base_Start(&TIM7_HandleType);
			 is_high = 1;
		
		}
		//while(HAL_GPIO_ReadPin(GPIOC,Echo)==1);
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_Pin) == 0 && is_high == 1)
		{
			HAL_TIM_Base_Stop(&TIM7_HandleType);
			time = __HAL_TIM_GET_COUNTER(&TIM7_HandleType);
			is_high = 0;
			Distance=__HAL_TIM_GET_COUNTER(&TIM7_HandleType)*340/200.0;
			//printf("Distance:%f cm\r\n",Distance);
		}
		HAL_NVIC_ClearPendingIRQ(EXTI2_IRQn);
	}
}


//定时器触发超声波
//void TIM4_IRQHandler(void)
//{
//	HAL_TIM_IRQHandler(&TIM4_HandleType);
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == TIM4)
//    {
//        // 触发超声波
//        HAL_GPIO_WritePin(GPIOC, Trig, GPIO_PIN_SET);
//        delay_us(15); // 持续15us高电平
//        HAL_GPIO_WritePin(GPIOC, Trig, GPIO_PIN_RESET);
//		HAL_NVIC_ClearPendingIRQ(TIM4_IRQn);
//    }

//}



float HC_SR04_GetDistance(void)
{	
	//Distance=time*340/200.0;

	//printf("Distance:%f cm\r\n",Distance);
	



}


void HC_SR04_Start(void)
{
	HAL_GPIO_WritePin(GPIOC,Trig,GPIO_PIN_SET);
	delay_us(15);
	HAL_GPIO_WritePin(GPIOC,Trig,GPIO_PIN_RESET);
}




//滤波，多次测量去平均值
void wave_filter(void)
{	int i = 0;
	while(i!=5)
	{
		//HC_SR04_Start();
		delay_ms(200);	
		Distance += Distance;
	}
	Distance = Distance/5.0;


}

//代码调试，点灯

void led_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIOA_Init;
	
    GPIOA_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOA_Init.Pin = GPIO_PIN_5;
    GPIOA_Init.Pull = GPIO_PULLUP;
    GPIOA_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIOA_Init);

}
void led_on()
{

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);

}

void led_off()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);

}