/**
 *  @file           control.h
 *  @brief          电机PID控制程序
 *  @version 1.0
 *  @author         李其建
 *  @date           2016年11月25日
 */


#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"



void Set_Pwm(int lmotor, int rmotor);


u8 Turn_Off(float angle, int voltage);
#endif
