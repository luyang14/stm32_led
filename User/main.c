/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   用3.5.0版本库建的工程模板
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO,ENABLE); //PB复用
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //TIM3重映射
	/********************************************/
}
void TIM3_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;//设置一个GPIO_InitStructure结构体。
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;//选择引脚6和7。
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//选择输出模式为复用推挽输出。
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置引脚最高输出速率为50MHz。
  GPIO_Init(GPIOA,&GPIO_InitStructure);//将设定好的参数初始化。

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//选择引脚5。
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//选择输出模式为复用推挽输出。
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置引脚最高输出速率为50MHz。
  GPIO_Init(GPIOB,&GPIO_InitStructure);//将设定好的参数初始化。
}
void TIM3_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//设置一个TIM_TimeBaseStructure结构体。
  TIM_OCInitTypeDef TIM_OCInitStructure;//设置一个TIM_OCInitStructure结构体。
  TIM_TimeBaseStructure.TIM_Period=1000-1;//个人理解就是计几个数。(由此可以得到PWM的周期)
  TIM_TimeBaseStructure.TIM_Prescaler=0;//设置用来作为 TIMx 时钟频率除数的预分频值。
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分割。
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//选择了计数器模式。
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//将设置好的参数初始化。
  TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置TIM输出模式PWM1。
  TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//选择输出比较状态(?)
  TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//TIM 输出比较极性高。
  TIM_OCInitStructure.TIM_Pulse=CCR1_Val;//设置了待装入捕获比较寄存器的脉冲值。
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);//将设定好的参数初始化给通道1。
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能TIM3在CCR1上的预装载寄存器。
  TIM_OCInitStructure.TIM_Pulse=CCR2_Val;
  TIM_OC2Init(TIM3,&TIM_OCInitStructure);//通道2
  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3,ENABLE);//使能TIM3在 ARR 上的预装载寄存器。
  TIM_Cmd(TIM3,ENABLE);//使能TIM3的外设
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

