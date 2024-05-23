#ifndef __HC_SR04_H
#define __HC_SR04_H

void HC_SR04_TIM7_Init(void);
void HC_SR04_TIM4_Init(void);
void HC_SR04_GPIO_Init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
float HC_SR04_GetDistance(void);
void HC_SR04_Start(void);
void wave_filter(void);
void led_init(void);
void led_on(void);
void led_off(void);

#endif
