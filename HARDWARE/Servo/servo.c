#include "stm32h7xx.h"                  // Device header

//初始化servo定时器

//extern void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);

TIM_HandleTypeDef TIM4_Handle;
TIM_OC_InitTypeDef TIM4_OC_InitType;

void TIM4_Init(void)
{
    TIM_Base_InitTypeDef TIM4_Base_Init;

    TIM4_Base_Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM4_Base_Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM4_Base_Init.Period  = 1800-1;
    TIM4_Base_Init.Prescaler = 1111-1;
    TIM4_Base_Init.RepetitionCounter = 0;

    TIM4_Handle.Instance = TIM4;
    TIM4_Handle.Init = TIM4_Base_Init;

    HAL_TIM_Base_Init(&TIM4_Handle);
	
	TIM_ClockConfigTypeDef TIM4_ClockConfigType;
    TIM4_ClockConfigType.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&TIM4_Handle, &TIM4_ClockConfigType);
	
    HAL_TIM_Base_Start(&TIM4_Handle);
}

void OC_servo_Init(void)
{
    TIM4_OC_InitType.OCMode = TIM_OCMODE_PWM1;
    TIM4_OC_InitType.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM4_OC_InitType.Pulse = 0;

    HAL_TIM_OC_Init(&TIM4_Handle);
    
    HAL_TIM_OC_ConfigChannel(&TIM4_Handle, &TIM4_OC_InitType, TIM_CHANNEL_4);

    HAL_TIM_OC_Start(&TIM4_Handle, TIM_CHANNEL_4);
}

void PWM_servo_Init(void)
{
    TIM4_OC_InitType.OCMode = TIM_OCMODE_PWM1;
    TIM4_OC_InitType.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM4_OC_InitType.Pulse = 0;

    HAL_TIM_PWM_Init(&TIM4_Handle);

    HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM4_OC_InitType, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&TIM4_Handle, TIM_CHANNEL_4);
}



void servo_pwm(void)
{
    TIM4_Init();
    OC_servo_Init();
    PWM_servo_Init();
}

void servo_setangle(uint8_t angle)
{
	
	TIM4->CCR4 = angle + 45;

}

