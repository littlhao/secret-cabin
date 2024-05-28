#include "stm32h7xx.h"  // Device header
#include "MPU_6050.h"
#include "usart.h"
#include "math.h"
#include "delay.h"

#define K 0   //融合平滑系数
#define RAD_TO_DEG 57.295779513082320876798154814105 // 180 / pi

I2C_HandleTypeDef I2C_HandleType;
uint8_t sdata , id , rdata,timeout = 100;
int16_t gyro_bias_x, gyro_bias_y, gyro_bias_z;


void MPU_Init(void)
{
	
	I2C_HandleType.Instance = I2C1;
    I2C_HandleType.Init.Timing = 0x00C0EAFF;  
    I2C_HandleType.Init.OwnAddress1 = 0;
    I2C_HandleType.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2C_HandleType.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2C_HandleType.Init.OwnAddress2 = 0;
    I2C_HandleType.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    I2C_HandleType.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2C_HandleType.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	
	HAL_I2C_Init(&I2C_HandleType);
	
	sdata = 0x09;
	HAL_I2C_Mem_Write(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_SMPLRT_DIV,I2C_MEMADD_SIZE_8BIT,&sdata,sizeof(sdata),timeout);
	sdata = 0x01;
	HAL_I2C_Mem_Write(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_PWR_MGMT_1,I2C_MEMADD_SIZE_8BIT,&sdata,sizeof(sdata),timeout);
	sdata = 0x00;
	HAL_I2C_Mem_Write(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_PWR_MGMT_2,I2C_MEMADD_SIZE_8BIT,&sdata,sizeof(sdata),timeout);
	sdata = 0x06;
	HAL_I2C_Mem_Write(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_CONFIG,I2C_MEMADD_SIZE_8BIT,&sdata,sizeof(sdata),timeout);
	sdata = 0x18;
	HAL_I2C_Mem_Write(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_CONFIG,I2C_MEMADD_SIZE_8BIT,&sdata,sizeof(sdata),timeout);
	sdata = 0x00;
	HAL_I2C_Mem_Write(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_CONFIG,I2C_MEMADD_SIZE_8BIT,&sdata,sizeof(sdata),timeout);
}	

uint8_t MPU6050_GetID(void)
{
	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_WHO_AM_I,I2C_MEMADD_SIZE_8BIT,&id,sizeof(id),timeout);
	return id;
}

//void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
//						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
//{
//	uint8_t DataH, DataL;
//	
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_XOUT_H,I2C_MEMADD_SIZE_8BIT,&DataH,sizeof(DataH),timeout);
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_XOUT_L,I2C_MEMADD_SIZE_8BIT,&DataL,sizeof(DataL),timeout);
//	*AccX = (DataH << 8) | DataL;
//	
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_YOUT_H,I2C_MEMADD_SIZE_8BIT,&DataH,sizeof(DataH),timeout);
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_YOUT_L,1,&DataL,sizeof(DataL),timeout);
//	*AccY = (DataH << 8) | DataL;
//	
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_ZOUT_H,I2C_MEMADD_SIZE_8BIT,&DataH,sizeof(DataH),timeout);
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_ACCEL_ZOUT_L,I2C_MEMADD_SIZE_8BIT,&DataL,sizeof(DataL),timeout);
//	*AccZ = (DataH << 8) | DataL;
//	
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_XOUT_H,I2C_MEMADD_SIZE_8BIT,&DataH,sizeof(DataH),timeout);
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_XOUT_L,I2C_MEMADD_SIZE_8BIT,&DataL,sizeof(DataL),timeout);
//	*GyroX = (DataH << 8) | DataL;
//	
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_YOUT_H,I2C_MEMADD_SIZE_8BIT,&DataH,sizeof(DataH),timeout);
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_YOUT_L,I2C_MEMADD_SIZE_8BIT,&DataL,sizeof(DataL),timeout);
//	*GyroY = (DataH << 8) | DataL;
//	
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_ZOUT_H,I2C_MEMADD_SIZE_8BIT,&DataH,sizeof(DataH),timeout);
//	HAL_I2C_Mem_Read(&I2C_HandleType,MPU6050_ADDRESS,MPU6050_GYRO_ZOUT_L,I2C_MEMADD_SIZE_8BIT,&DataL,sizeof(DataL),timeout);
//	*GyroZ = (DataH << 8) | DataL;
//}
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ)
//                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    uint8_t DataH, DataL;
    HAL_StatusTypeDef ret;

    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, sizeof(DataH), timeout);
    if (ret != HAL_OK) { printf("get ax_h error \r\n"); return; }
    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, sizeof(DataL), timeout);
    if (ret != HAL_OK) { printf("get ax_l error \r\n"); return; }
    *AccX = (DataH << 8) | DataL;

    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_ACCEL_YOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, sizeof(DataH), timeout);
    if (ret != HAL_OK) { printf("get ay_h error \r\n"); return; }
    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_ACCEL_YOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, sizeof(DataL), timeout);
    if (ret != HAL_OK) { printf("get ay_l error \r\n"); return; }
    *AccY = (DataH << 8) | DataL;

    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, sizeof(DataH), timeout);
    if (ret != HAL_OK) { printf("get az_h error \r\n"); return; }
    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, sizeof(DataL), timeout);
    if (ret != HAL_OK) { printf("get az_l error \r\n"); return; }
    *AccZ = (DataH << 8) | DataL;

//    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, sizeof(DataH), timeout);
//    if (ret != HAL_OK) { printf("get gx_h error \r\n"); return; }
//    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_XOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, sizeof(DataL), timeout);
//    if (ret != HAL_OK) { printf("get gx_l error \r\n"); return; }
//    *GyroX = (DataH << 8) | DataL;

//    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_YOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, sizeof(DataH), timeout);
//    if (ret != HAL_OK) { printf("get gy_h error \r\n"); return; }
//    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_YOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, sizeof(DataL), timeout);
//    if (ret != HAL_OK) { printf("get gy_l error \r\n"); return; }
//    *GyroY = (DataH << 8) | DataL;

//    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_ZOUT_H, I2C_MEMADD_SIZE_8BIT, &DataH, sizeof(DataH), timeout);
//    if (ret != HAL_OK) { printf("get gz_h error \r\n"); return; }
//    ret = HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_ZOUT_L, I2C_MEMADD_SIZE_8BIT, &DataL, sizeof(DataL), timeout);
//    if (ret != HAL_OK) { printf("get gz_l error \r\n"); return; }
//    *GyroZ = (DataH << 8) | DataL;
}





void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_I2C1_CLK_ENABLE(); }

    GPIO_InitTypeDef GPIOB_Init;
	GPIOB_Init.Alternate = GPIO_AF4_I2C1;
    GPIOB_Init.Mode = GPIO_MODE_AF_OD;
    GPIOB_Init.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIOB_Init.Pull = GPIO_NOPULL;
    GPIOB_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIOB_Init);


}

void MPU6050_GetGyroData(int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    // ??????? MPU6050 ??????????
    uint8_t data[6];
    HAL_I2C_Mem_Read(&I2C_HandleType, MPU6050_ADDRESS, MPU6050_GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 6, timeout);
    *GyroX = (int16_t)(data[0] << 8 | data[1]);
    *GyroY = (int16_t)(data[2] << 8 | data[3]);
    *GyroZ = (int16_t)(data[4] << 8 | data[5]);
}



void calibrate_gyroscope(int16_t *gyro_bias_x, int16_t *gyro_bias_y, int16_t *gyro_bias_z)
{
    int32_t gyro_x_sum = 0, gyro_y_sum = 0, gyro_z_sum = 0;
    int num_samples = 1000;  // ????

    for (int i = 0; i < num_samples; i++) {
        int16_t gyro_x, gyro_y, gyro_z;
        MPU6050_GetGyroData(&gyro_x, &gyro_y, &gyro_z);
        
        gyro_x_sum += gyro_x;
        gyro_y_sum += gyro_y;
        gyro_z_sum += gyro_z;
        delay_ms(1);  // ?? 1 ms
    }

    *gyro_bias_x = gyro_x_sum / num_samples;
    *gyro_bias_y = gyro_y_sum / num_samples;
    *gyro_bias_z = gyro_z_sum / num_samples;
}




void get_corrected_gyro_data(int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    int16_t raw_gyro_x, raw_gyro_y, raw_gyro_z;
	
	calibrate_gyroscope(&gyro_bias_x, &gyro_bias_y, &gyro_bias_z);
    MPU6050_GetGyroData(&raw_gyro_x, &raw_gyro_y, &raw_gyro_z);

    *GyroX = raw_gyro_x - gyro_bias_x;
    *GyroY = raw_gyro_y - gyro_bias_y;
    *GyroZ = raw_gyro_z - gyro_bias_z;
}



void data_processing(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ, double *ypr)
{
    double roll_acc, roll_gvro = 0.0, pitch_acc, pitch_gvro = 0.0, yaw = 0.0;
    double dr_t, dp_t, dy_t;

    // 加速度计
    roll_acc = atan2((double)(*AccY), (double)(*AccZ));
    pitch_acc = -atan2((double)(*AccX), sqrt(pow((double)(*AccY), 2) + pow((double)(*AccZ), 2)));

    // 陀螺仪
    dr_t = (double)(*GyroX) + tan(ypr[1]) * sin(ypr[2]) * (double)(*GyroY) + tan(ypr[1]) * cos(ypr[2]) * (double)(*GyroZ);
    dp_t = cos(ypr[2]) * (double)(*GyroY) - sin(ypr[2]) * (double)(*GyroZ);
    dy_t = (sin(ypr[2]) / cos(ypr[1])) * (double)(*GyroY) + (cos(ypr[2]) / sin(ypr[1])) * (double)(*GyroZ);

    roll_gvro += dr_t * 0.01;
    pitch_gvro += dp_t * 0.01;
    yaw += dy_t * 0.01;

    // 状态融合
    ypr[0] = yaw;
    ypr[1] = pitch_acc * (1 - K) + pitch_gvro * K;
    ypr[2] = roll_acc * (1 - K) + roll_gvro * K;
	
	    // 转化为角度
    ypr[0] *= RAD_TO_DEG;
    ypr[1] *= RAD_TO_DEG;
    ypr[2] *= RAD_TO_DEG;
}

