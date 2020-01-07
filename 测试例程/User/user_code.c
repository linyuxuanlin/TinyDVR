#include "user_code.h"

void Init(void)
{
	Encoder_TIM_Mode_Config(0, 65535);
	Motor_Tim_Config();
	TIM6_CounterMode(49, 7199);
}
