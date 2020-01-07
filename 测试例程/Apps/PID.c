/*
  *******************************************************************************
  * @file    PID.c
  * @author  Luu-yy
  * @version  
  * @date    
  * @brief   PID���ܺ���
  ******************************************************************************
  */

#include "PID.h"

/*����޷�*/
void PWM_Limit(int motor)
{
	int Amplitude = 7200;
    if(motor > Amplitude)
		motor = Amplitude;
    if(motor < -Amplitude)
		motor = -Amplitude;
}

/**
* @brief	     ����ʽPID-������ʼ��(�Թ����ã�λ��ʽ��������ȥҪ�����Լ�����Ӧ����û����ģ�
* @param [in]    ����ʽPIDָ��
*				 [in] Kp   ����  ��Ҫ�������Ӧ�ٶ�
*				 [in] Ki   ����  ������̬���
*				 [in] Kd   ΢��  ����ƫ��
*				 ����������Կ��ĵ����Լ��ٶ��������������κܶ�ʱ�򻹿��о�
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
* @brief	     λ��ʽPID-������ʼ��
* @param [in]    λ��ʽPIDָ��
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
