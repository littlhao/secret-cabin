#include "stm32h7xx.h"                  // Device header



//初始化pwm定时器2四个通道,PA0 - PA3复用GPIO为TIM2_CH1 - CH4

TIM_HandleTypeDef TIM2_Handle;
TIM_OC_InitTypeDef TIM2_OC_InitType;

void TIM2_Init(void)
{
    TIM_Base_InitTypeDef TIM2_Base_Init;

    TIM2_Base_Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM2_Base_Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM2_Base_Init.Period  = 100-1;
    TIM2_Base_Init.Prescaler = 100-1;
    TIM2_Base_Init.RepetitionCounter = 0;

    TIM2_Handle.Instance = TIM2;
    TIM2_Handle.Init = TIM2_Base_Init;

    HAL_TIM_Base_Init(&TIM2_Handle);
	
	TIM_ClockConfigTypeDef TIM2_ClockConfigType;
    TIM2_ClockConfigType.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&TIM2_Handle, &TIM2_ClockConfigType);
	
    HAL_TIM_Base_Start(&TIM2_Handle);
}

void OC_Init(void)
{
    TIM2_OC_InitType.OCMode = TIM_OCMODE_PWM1;
    TIM2_OC_InitType.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM2_OC_InitType.Pulse = 0;

    HAL_TIM_OC_Init(&TIM2_Handle);
    
    HAL_TIM_OC_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_1);
    HAL_TIM_OC_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_2);
    HAL_TIM_OC_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_3);
    HAL_TIM_OC_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_4);

    HAL_TIM_OC_Start(&TIM2_Handle, TIM_CHANNEL_1);
    HAL_TIM_OC_Start(&TIM2_Handle, TIM_CHANNEL_2);
    HAL_TIM_OC_Start(&TIM2_Handle, TIM_CHANNEL_3);
    HAL_TIM_OC_Start(&TIM2_Handle, TIM_CHANNEL_4);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
    {
	__HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIOA_Init;
    GPIOA_Init.Alternate = GPIO_AF1_TIM2;
    GPIOA_Init.Mode = GPIO_MODE_AF_PP;
    GPIOA_Init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIOA_Init.Pull = GPIO_PULLUP;
    GPIOA_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIOA_Init);
	}
	else if(htim->Instance == TIM4)
	{
	    __HAL_RCC_TIM4_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();

		GPIO_InitTypeDef GPIOD_Init;
		GPIOD_Init.Alternate = GPIO_AF2_TIM4;
		GPIOD_Init.Mode = GPIO_MODE_AF_PP;
		GPIOD_Init.Pin = GPIO_PIN_15;
		GPIOD_Init.Pull = GPIO_PULLUP;
		GPIOD_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOD, &GPIOD_Init);
	}

}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
    // No need to enable clock again, it's already done in HAL_TIM_Base_MspInit
}






