/*
  ******************************************************************************
  * @file   bsp_nvic.c
  * @author  
  * @version  
  * @date    
  * @brief  NVIC中断优先级应用函数接口
  ******************************************************************************
  */

#include "bsp_nvic.h"

/**
  * @brief  NVIC中断优先级配置
  * @param  IRQChannel 	  	  中断源  
  *		    MainPriority	  主优先级
  *			SubPriority		  抢占式优先级
  * @retval None
  */
	
void NVIC_Config(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;      
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;    
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}
