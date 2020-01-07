/*
 ******************************************************************************
 * @file    Motor.c
 * @author
 * @version
 * @date
 * @brief   ������������·PWMֱ�ӿ��Ƶ������ת
 *          ��С�������������õ��IN1 IN2,1·pwm���
 *           �������ö�ʱ��8ͨ��1��2��ע�ͺܶ�һ���Ͳ�д�ˣ�
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
	/*���Ĵ�����������Ĭ��ֵ*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	//����ʱ��
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 7199;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

	TIM_OCInitStruct.TIM_Pulse = 0;
	//��ʼ��CCR������ռ�ձȣ�
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	//���ʹ��
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	//PWM����ģʽ
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	//�������Ч����ʼ���θߣ�

	/*��ʼ��ͨ��*/
	TIM_OC1Init(TIM8, &TIM_OCInitStruct);
	TIM_OC2Init(TIM8, &TIM_OCInitStruct);
    TIM_Cmd(TIM8, ENABLE);

	/*Ԥװ��ʹ��*/
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	/*�����ʹ��*/
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	/*ʹ��TIMx��ARR��Ԥװ�ؼĴ���*/
}
