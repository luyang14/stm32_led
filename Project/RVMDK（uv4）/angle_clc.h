#ifndef __IMU_H
#define __IMU_H
 
#include "common.h"
 
#include <math.h>
#define M_PI  (float)3.1415926535
 
//��������̬��������ⲿ�������
extern volatile float IMU_Pitch,IMU_Roll,IMU_Yaw;  //��λ ��
//�����ǵ������
extern volatile float IMU_GYROx, IMU_GYROy, IMU_GYROz;//��λ  ��ÿ��
extern float acc_vector ;  //��ǰ���ٶȸ�Ӧ��������  M/S^2��
//Mini IMU AHRS �����API
void IMU_init(void); //��ʼ��
void IMU_getYawPitchRoll(float * ypr); //������̬  ��Ҫ���ڵ���
//uint32_t micros(void);//��ȡϵͳ�ϵ���ʱ��  ��λ us
 
#endif
 