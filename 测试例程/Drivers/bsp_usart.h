#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "user_common.h"

/********USART1_Pin_define********/
#define USART1_TX_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USART1_TX_GPIO_PORT         GPIOA
#define USART1_TX_Pin          	    GPIO_Pin_9
#define USART1_TX_PINSOURCE			GPIO_PinSource9

#define USART1_RX_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USART1_RX_GPIO_PORT         GPIOA
#define USART1_RX_Pin           	GPIO_Pin_10
#define USART1_RX_PINSOURCE			GPIO_PinSource10
/********USART1_Pin_define_END********/

/********USART3_Pin_define********/
#define USART3_TX_GPIO_CLK          RCC_APB2Periph_GPIOB
#define USART3_TX_GPIO_PORT         GPIOB
#define USART3_TX_Pin          	 	GPIO_Pin_10
#define USART3_TX_PINSOURCE		    GPIO_PinSource10

#define USART3_RX_GPIO_CLK          RCC_APB2Periph_GPIOB
#define USART3_RX_GPIO_PORT         GPIOB
#define USART3_RX_Pin           	GPIO_Pin_11
#define USART3_RX_PINSOURCE			GPIO_PinSource11
/********USART3_Pin_define_END********/

void USART1_QuickInit(uint32_t USART_BaudRate);

void USART3_QuickInit(uint32_t USART_BaudRate);

void USART_sendChar(USART_TypeDef* USARTx, char ch);

int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __BSP_USART_H */
