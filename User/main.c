/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  */
  
#include "stm32f10x.h"
u16 CCR1_Val=1000;
u16 CCR2_Val=0;
u8 a=0;
void Delay(__IO u32 nCount)
{
  while(nCount--);
}
void RCC_Config(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*********************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO,ENABLE); //PB����
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //TIM3��ӳ��
	/********************************************/
}
void TIM3_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;//����һ��GPIO_InitStructure�ṹ�塣
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;//ѡ������6��7��
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//ѡ�����ģʽΪ�������������
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//������������������Ϊ50MHz��
  GPIO_Init(GPIOA,&GPIO_InitStructure);//���趨�õĲ�����ʼ����

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//ѡ������5��
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//ѡ�����ģʽΪ�������������
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//������������������Ϊ50MHz��
  GPIO_Init(GPIOB,&GPIO_InitStructure);//���趨�õĲ�����ʼ����
}
void TIM3_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//����һ��TIM_TimeBaseStructure�ṹ�塣
  TIM_OCInitTypeDef TIM_OCInitStructure;//����һ��TIM_OCInitStructure�ṹ�塣
  TIM_TimeBaseStructure.TIM_Period=1000-1;//���������ǼƼ�������(�ɴ˿��Եõ�PWM������)
  TIM_TimeBaseStructure.TIM_Prescaler=0;//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ��
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ�ӷָ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//ѡ���˼�����ģʽ��
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//�����úõĲ�����ʼ����
  TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//����TIM���ģʽPWM1��
  TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//ѡ������Ƚ�״̬(?)
  TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//TIM ����Ƚϼ��Ըߡ�
  TIM_OCInitStructure.TIM_Pulse=CCR1_Val;//�����˴�װ�벶��ȽϼĴ���������ֵ��
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);//���趨�õĲ�����ʼ����ͨ��1��
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ�����
  TIM_OCInitStructure.TIM_Pulse=CCR2_Val;
  TIM_OC2Init(TIM3,&TIM_OCInitStructure);//ͨ��2
  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ʹ��TIM3�� ARR �ϵ�Ԥװ�ؼĴ�����
  TIM_Cmd(TIM3,ENABLE);//ʹ��TIM3������
}
int main(void)
{
    RCC_Config();
 TIM3_GPIO_Config();
 TIM3_Mode_Config();
 while(1)
 {
     if(CCR1_Val>0&&a<40&&CCR2_Val<1000)
     {
       CCR1_Val-=25;
       CCR2_Val+=25;
       TIM3_Mode_Config();
       a++;
       Delay(0XFFFF); 
			 Delay(0XFFFF);
       Delay(0XFFFF); 
			 Delay(0XFFFF); 
     }
    else
    {
       CCR1_Val+=25;
       CCR2_Val-=25;
       TIM3_Mode_Config();
       Delay(0XFFFF);
			Delay(0XFFFF); 
			
       a++;
    if(a==80)a=0;
     }
 }
}

/*********************************************END OF FILE**********************/

