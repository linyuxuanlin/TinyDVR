#include "control.h"

int Motor;
int Encoder;
int Target_velocity = 20;     //Ŀ���ٶ�

void  Set_Pwm(int motor)
{
	if (motor > 0)
		PWMB = 7200, PWMA= 7200 - motor;
	else 	              
		PWMA = 7200, PWMB= 7200 + motor;
}
