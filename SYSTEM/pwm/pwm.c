#include "stm32h7xx.h"  // Device header

TIM_HandleTypeDef TIM2_Handle;
TIM_OC_InitTypeDef TIM2_OC_InitType;

void TIM2_Init(void)
{
    TIM_Base_InitTypeDef TIM2_Base_Init;

    TIM2_Base_Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM2_Base_Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM2_Base_Init.Period  = 100-1;
    TIM2_Base_Init.Prescaler = 2000-1;
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

void PWM_Init(void)
{
    TIM2_OC_InitType.OCMode = TIM_OCMODE_PWM1;
    TIM2_OC_InitType.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM2_OC_InitType.Pulse = 0;

    HAL_TIM_PWM_Init(&TIM2_Handle);

    HAL_TIM_PWM_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handle, &TIM2_OC_InitType, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&TIM2_Handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM2_Handle, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&TIM2_Handle, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&TIM2_Handle, TIM_CHANNEL_4);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIOA_Init;
    GPIOA_Init.Alternate = GPIO_AF1_TIM2;
    GPIOA_Init.Mode = GPIO_MODE_AF_PP;
    GPIOA_Init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIOA_Init.Pull = GPIO_PULLUP;
    GPIOA_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIOA_Init);
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
    // No need to enable clock again, it's already done in HAL_TIM_Base_MspInit
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    // No need to enable clock again, it's already done in HAL_TIM_Base_MspInit
}

void pwm(void)
{
    TIM2_Init();
    OC_Init();
    PWM_Init();
}


