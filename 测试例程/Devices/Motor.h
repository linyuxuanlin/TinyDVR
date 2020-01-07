#ifndef __MOTOR_H
#define __MOTOR_H

#include "user_common.h"

extern incrementalpid_t pid;
extern positionpid_t PID;

void Motor_Tim_Config(void);

#endif  /*__MOTOR_H*/
