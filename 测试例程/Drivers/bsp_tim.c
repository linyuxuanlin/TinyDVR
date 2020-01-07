/*
  ******************************************************************************
  * @file    bsp_tim.c
  * @author   
  * @version  
  * @date    
  * @brief   TIMӦ�ú����ӿ�
  ******************************************************************************
  */

#include "bsp_tim.h"

/**
  * @brief  ������ʱ��TIM6��Ϊ����ģʽ��ʼ��
  * @param  prescaler 	   ʱ��Ԥ��Ƶ
  *		    period	       ��ʱ����װ�ؼĴ�����ֵ(arr)
  *		    ��ʱ����ʱƵ��:ϵͳʱ��Ƶ��/Ԥ��Ƶ/��װ��ֵ
  * @retval None
  */
	
void TIM6_CounterMode(u16 prescaler, u16 period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
	/* ����ʱ���ṹ�� */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	//ʹ�ܶ�ʱ��ʱ��
  
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;   
	//���ö�ʱ��ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_Period = period;         
	//�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	//��ʼ��TIM6ʱ�������λ

	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	//��������жϣ���ֹһ���ж���������ж�
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	//�򿪶�ʱ�������ж�

	NVIC_Config(TIM6_IRQn, 1, 0);
	/*�����ж����ȼ�*/
	TIM_Cmd(TIM6, ENABLE);
	//ʹ�ܶ�ʱ��
}
