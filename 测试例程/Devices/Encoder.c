/*
 ******************************************************************************
 * @file    Encoder.c
 * @author
 * @version
 * @date
 * @brief   编码器AB相（TIM4 CH1  PB6  CH2  PB7)
 ******************************************************************************
 */

#include "Encoder.h"

void Encoder_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*Enable GPIOB Clock*/

	/*Channel pin configuration of timer corresponding to phase AB used in encoder*/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Encoder_TIM_Mode_Config(uint32_t psc1,uint32_t arr1)
{ 	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
    Encoder_TIM_GPIO_Config();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//配置时基
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = arr1;
	//配置自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc1;
	//配置定时器时钟分频
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	//时钟分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	//重复计数器无效0
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	//配置输入
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	//输入器不分频
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	//上升沿捕获
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//映射到IC1
	TIM_ICInitStruct.TIM_ICFilter = 0;
	//不滤波
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	//使能编码器模式3 0x0003
	
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
//    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM4,0);
	
	TIM_Cmd(TIM4, ENABLE);
}


/*编码器读取对应CNT计数寄存器的值*/
int Read_Encoder(u8 TIMX)   
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
		 case 1:  Encoder_TIM= (short)TIM1 -> CNT;  TIM1 -> CNT=0;break;
	     case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=0;break;
		 case 8:  Encoder_TIM= (short)TIM8 -> CNT;  TIM8 -> CNT=0;break;
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;    /*CNT清零*/
}
