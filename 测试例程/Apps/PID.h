#ifndef __PID_H
#define __PID_H

#include "user_common.h"

void PWM_Limit(int motor);
int Incremental_PID(int Encoder, int Target);
int Position_PID(int Encoder, int Target);

#endif   /* __PID_H */
