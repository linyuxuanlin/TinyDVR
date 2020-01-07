/*
 ******************************************************************************
 * @file    bsp_usart.c
 * @author
 * @version
 * @date
 * @brief   USARTӦ�ú����ӿ�
 ******************************************************************************
 */

#include "bsp_usart.h"

/**
* @brief  USART1���ٳ�ʼ����û��ң������
* @param  USART_BaudRate 	����������
* @retval None
* @Using  ���ڽ���DR16���ջ�Dbus����
*/
void USART1_QuickInit(uint32_t USART_BaudRate) {

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(USART1_TX_GPIO_CLK, ENABLE);
	/* ʹ�� GPIO ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/* ʹ�� USART1 ʱ�� */

	/* ����Tx����  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

	/* ����USART ģʽ */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* ���������ã�USART_BAUDRATE */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ���ݳ���(����λ+У��λ)��8 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */

	USART_Init(USART1, &USART_InitStructure);
	/* ���USART��ʼ������ */
	NVIC_Config(USART1_IRQn, 0, 1);
	/* �����ж����ȼ����� */

	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	//����жϱ�־
	USART_Cmd(USART1, ENABLE);
	/* ʹ�ܴ��� */
}


/**
* @brief  USART3���ٳ�ʼ��
* @param  USART_BaudRate 	����������
* @retval None
* @Using 	����pc�˷��ͣ����յ�����Ϣ
*/
void USART3_QuickInit(uint32_t USART_BaudRate) {

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� GPIO ʱ�� */
	RCC_APB1PeriphClockCmd(USART3_TX_GPIO_CLK, ENABLE);
	/* ʹ�� USART3ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* ����Tx����  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);

	/* ���ô�USART ģʽ */
	/* ���������ã�USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* ���ݳ���(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(USART3, &USART_InitStructure);

	/* ʹ�ܴ��ڽ����ж� */
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

	/* ʹ�ܴ��� */
	USART_Cmd(USART3, ENABLE);
}


/**
* @brief  USART����һ���ַ�
* @param  USARTx 	USART����
*		    ch   		�ַ�
* @retval None
*/
void USART_sendChar(USART_TypeDef* USARTx, char ch)
{
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(USARTx, (uint8_t)ch);
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}


//�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(USART3, (uint8_t)ch);

	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);

	return (ch);
}

  //�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

