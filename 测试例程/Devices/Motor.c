/*
 ******************************************************************************
 * @file    Motor.c
 * @author
 * @version
 * @date
 * @brief   （新驱动）两路PWM直接控制电机正反转
 *          （小驱动）另外配置电机IN1 IN2,1路pwm输出
 *           这里配置定时器8通道1，2（注释很多一样就不写了）
 ******************************************************************************
 */

#include "Motor.h"

 incrementalpid_t pid;
positionpid_t PID;

void Motor_Tim_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	//	TIM_DeInit(TIM8);    
	/*将寄存器重新设置默认值*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	//配置时基
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 7199;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

	TIM_OCInitStruct.TIM_Pulse = 0;
	//初始化CCR（设置占空比）
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	//输出使能
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	//PWM工作模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	//输出高有效（起始波形高）

	/*初始化通道*/
	TIM_OC1Init(TIM8, &TIM_OCInitStruct);
	TIM_OC2Init(TIM8, &TIM_OCInitStruct);
    TIM_Cmd(TIM8, ENABLE);

	/*预装载使能*/
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	/*主输出使能*/
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	/*使能TIMx在ARR上预装载寄存器*/
}
