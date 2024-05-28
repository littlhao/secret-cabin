#ifndef __MPU_6050_H
#define __MPU_6050_H

#include "MPU6050_Reg.h"
#define MPU6050_ADDRESS		0xD0

void MPU_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ); 
//						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void data_processing(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ ,double *ypr);
void get_corrected_gyro_data(int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);


#endif


