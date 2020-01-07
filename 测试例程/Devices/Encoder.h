#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

void Encoder_TIM_Mode_Config(uint32_t psc1,uint32_t arr1);
int Read_Encoder(u8 TIMX);


#endif  /*__ENCODER_H*/
