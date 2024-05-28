#include "stm32h7xx.h"                  // Device header
#include "main.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"
#include "motor.h"
#include "HC-SR04.h"
#include "MPU_6050.h"
#include "IMU.h"
#include "servo.h"

void obstruction_info(void);

float Distance = 0;
uint8_t ID , angel = 0;
int16_t AX, AY, AZ, GX, GY, GZ;
int flag[12];


int main(void)
{

    double ypr[3]; // ŷ��������:Yaw, Pitch, Roll
	int flag[12];

	
	HAL_Init();
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
	delay_init(400);
	uart_init(115200);
	pwm();
	HC_SR04_GPIO_Init();
	HC_SR04_TIM7_Init();
//	HC_SR04_TIM4_Init();
	led_init();
	MPU_Init();
	servo_pwm();

	
	motor_left_ctl(50);
	motor_right_ctl(50);
	while(1)
	{
		obstruction_info();
		//MPU6050_GetData(&AX,&AY,&AZ);
//		get_corrected_gyro_data(&GX,&GY,&GZ);
//		data_processing(&AX,&AY,&AZ,&GX,&GY,&GZ,ypr);
//		ID = MPU6050_GetID();
	
		//printf("obstruction information angle:%d, Distance:%f cm\r\n",angel, Distance);
//		printf("ID:%d \r\n",ID);
//		printf("Yaw: %f, Pitch: %f, Roll: %f \r\n", ypr[0], ypr[1], ypr[2]);
//		printf("AX:%d \r\n",AX);
//		printf("AY:%d \r\n",AY);
//		printf("AZ:%d \r\n",AZ);
//		printf("GX:%d \r\n",GX);
//		printf("GY:%d \r\n",GY);
//		printf("GZ:%d \r\n",GZ);
		//HC_SR04_Start();
		//led_on();
		
		//HC_SR04_GetDistance();
//		if(Distance > 8)
//		{
//			led_off();
//		}
//		else
//		{
//			led_on();
//		}
//		//Distance = HC_SR04_GetDistance();
//		printf("Distance:%f cm\r\n",Distance);
		//delay_ms(100);
		//led_off();
		
	
	}
		
}



//void autodrive (int a, int b, int PID)
//	{
//    if(Distance<20)          //�򵥱���
//	 {
//					Go_stop();
//		}else if (Distance>20)
//		{
//		if(X==1)                //���ͣ��
//		{
//					Go_stop();
//		}else if (X==0||X==2)   //�޺��̵ƻ����̵Ƽ�����ʻ ��������
//		{
//		 if(Y>50)               //С��ƫ��  
//		 {
//		  Go_forward(PID,b);
//		 }else if(Y<50)         //С��ƫ��  
//			{
//			Go_forward(a,PID);
//			}
//		}
//	}
//}

////λ��ʽPID������
//int Position_PID (int Encoder,int Target) //Ŀ��ֵ50  ����ֵY�����Ƕ�
//  { 	
//	 float Position_KP=160,Position_KI=0.01,Position_KD=90;
//   static float Bias,Pwm,Integral_bias,Last_Bias;
//   Bias=Encoder-Target; //����ƫ��
//   Integral_bias+=Bias; //���ƫ��Ļ���	     
//   Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       
//   Last_Bias=Bias;       //������һ��ƫ�� 
//   return Pwm;           //���
//  }

void obstruction_info(void)
{	
	
	servo_setangle(angel);
	angel += 1;
	if(angel % 15 == 0)
	{
		if(angel > 180)
		{angel = 0;}
	HC_SR04_Start();
	printf("obstruction information angle:%d, Distance:%f cm\r\n",(angel - 90), Distance);
	if(Distance < 5)
		flag[angel/15] = 1; 
	
	}

}


	
