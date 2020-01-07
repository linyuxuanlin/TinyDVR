/**
  ******************************************************************************
  * @file    bsp_delay.c
  * @author  
  * @version  
  * @date     
  * @brief   ��ʱӦ�ú����ӿ�
  ******************************************************************************
  */
  
#include "bsp_delay.h"

/**
  * @brief  ���뼶��ʱ
  * @param  _ms ��ʱ������
  * @retval None
  */
void delay_ms(u32 _ms)
{
	u32 i;

	SysTick_Config(SystemCoreClock/1000);         //1ms��ʱ��

	for( i = 0; i < _ms; i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));        //�ж��Ƿ�������
	}

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    //��0�رռ�����
}

/**
  * @brief  ΢�뼶��ʱ
  * @param  _us ��ʱ΢����
  * @retval None
  */
void delay_us(u32 _us)
{
	u32 i;
	SysTick_Config(SystemCoreClock/1000000);     

	for( i = 0; i < _us; i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
