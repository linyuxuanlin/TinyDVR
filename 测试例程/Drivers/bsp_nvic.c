/*
  ******************************************************************************
  * @file   bsp_nvic.c
  * @author  
  * @version  
  * @date    
  * @brief  NVIC�ж����ȼ�Ӧ�ú����ӿ�
  ******************************************************************************
  */

#include "bsp_nvic.h"

/**
  * @brief  NVIC�ж����ȼ�����
  * @param  IRQChannel 	  	  �ж�Դ  
  *		    MainPriority	  �����ȼ�
  *			SubPriority		  ��ռʽ���ȼ�
  * @retval None
  */
	
void NVIC_Config(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//�����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;      
	//���������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;
	//������ռʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;    
	//ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}
