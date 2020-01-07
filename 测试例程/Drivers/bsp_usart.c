/*
 ******************************************************************************
 * @file    bsp_usart.c
 * @author
 * @version
 * @date
 * @brief   USART应用函数接口
 ******************************************************************************
 */

#include "bsp_usart.h"

/**
* @brief  USART1快速初始化（没加遥控器）
* @param  USART_BaudRate 	波特率设置
* @retval None
* @Using  用于接收DR16接收机Dbus数据
*/
void USART1_QuickInit(uint32_t USART_BaudRate) {

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(USART1_TX_GPIO_CLK, ENABLE);
	/* 使能 GPIO 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/* 使能 USART1 时钟 */

	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置USART 模式 */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* USART模式控制：同时使能接收和发送 */

	USART_Init(USART1, &USART_InitStructure);
	/* 完成USART初始化配置 */
	NVIC_Config(USART1_IRQn, 0, 1);
	/* 串口中断优先级配置 */

	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	/* 使能串口空闲中断 */
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	//清除中断标志
	USART_Cmd(USART1, ENABLE);
	/* 使能串口 */
}


/**
* @brief  USART3快速初始化
* @param  USART_BaudRate 	波特率设置
* @retval None
* @Using 	用于pc端发送，接收调试信息
*/
void USART3_QuickInit(uint32_t USART_BaudRate) {

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 GPIO 时钟 */
	RCC_APB1PeriphClockCmd(USART3_TX_GPIO_CLK, ENABLE);
	/* 使能 USART3时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART3, &USART_InitStructure);

	/* 使能串口接收中断 */
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* 使能串口空闲中断 */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

	/* 使能串口 */
	USART_Cmd(USART3, ENABLE);
}


/**
* @brief  USART发送一个字符
* @param  USARTx 	USART外设
*		    ch   		字符
* @retval None
*/
void USART_sendChar(USART_TypeDef* USARTx, char ch)
{
	/* 发送一个字节数据到串口 */
	USART_SendData(USARTx, (uint8_t)ch);
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}


//重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口 */
	USART_SendData(USART3, (uint8_t)ch);

	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);

	return (ch);
}

  //重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

