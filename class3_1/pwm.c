/*
 * pwm.c
 *
 *  Created on: 2022��3��14��
 *      Author: z
 */


#include "pwm.h"
int i=512;
void pwmadd(){
    i+=5;
  if(i>=512)i=512;
}
void pwmdecr(){
    i-=5;
  if(i<=0)i=0;
}

void pwmplay(){
    TA0CCR1=i;
    __delay_cycles(160000);
}
