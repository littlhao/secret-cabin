#ifndef __PWM_H
#define __PWM_H


void TIM2_Init(void);
void OC_Init(void);
void pwm_init(void);
void pwm(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);


#endif
