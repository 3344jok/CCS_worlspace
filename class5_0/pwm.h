/*
 * pwm.h
 *
 *  Created on: 2022Äê3ÔÂ14ÈÕ
 *      Author: z
 */

#ifndef PWM_H_
#define PWM_H_
#include <msp430.h>

extern int i;
extern void pwmadd();
extern void pwmdecr();
extern void pwmplay();
extern void pwmadj(int target);
extern void pwmturnoff();
#endif /* PWM_H_ */
