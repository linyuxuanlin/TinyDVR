/*
  *******************************************************************************
  * @file    PID.c
  * @author  Luu-yy
  * @version  
  * @date    
  * @brief   PID功能函数
  ******************************************************************************
  */

#include "PID.h"

/*输出限幅*/
void PWM_Limit(int motor)
{
	int Amplitude = 7200;
    if(motor > Amplitude)
		motor = Amplitude;
    if(motor < -Amplitude)
		motor = -Amplitude;
}

/**
* @brief	     增量式PID-参数初始化(试过可用，位置式后来加上去要你们自己试试应该是没问题的）
* @param [in]    增量式PID指针
*				 [in] Kp   比例  主要是提高响应速度
*				 [in] Ki   积分  消除稳态误差
*				 [in] Kd   微分  抑制偏差
*				 具体解析可以看文档和自己百度慢慢摸索，调参很多时候还靠感觉
* @retval        
*/
int Incremental_PID(int Encoder, int Target)
{
	pid.Kp = -150;    
	pid.Ki = -40;
	pid.Kd = 0;

	pid.err = Encoder - Target;
	pid.pwm += pid.Kp*(pid.err - pid.err_last) + pid.Ki*pid.err + pid.Kd*(pid.err - 2 * pid.err_last + pid.err_beforeLast);

	if (pid.pwm>7200)
		pid.pwm = 7200;
	else if (pid.pwm<-7200)
		pid.pwm = -7200;

	pid.err_beforeLast = pid.err_last;
	pid.err_last = pid.err;
	
	return pid.pwm;
}

/**
* @brief	     位置式PID-参数初始化
* @param [in]    位置式PID指针
*				 [in] Kp
*				 [in] Ki
*				 [in] kd
* @retval 
*/
int Position_PID(int Encoder, int Target)
{
	PID.Kp = 0;
	PID.Ki = 0;
	PID.Kd = 0;

	PID.err = Encoder - Target;
	PID.integral_err += PID.err;

	PID.pwm += PID.Kp*PID.err + PID.Ki*PID.integral_err + PID.Kd*(PID.err - PID.err_last);

	if (PID.pwm>7200)
		PID.pwm = 7200;
	else if (PID.pwm<-7200)
		PID.pwm = -7200;

	PID.err_last = PID.err;

	return PID.pwm;
}
