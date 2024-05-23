#include "stm32h7xx.h"  // Device header
#include "timer.h"


extern TIM_HandleTypeDef TIM2_Handle;
extern TIM_OC_InitTypeDef TIM2_OC_InitType;


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


