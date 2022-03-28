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
  if(i<=0)i=50;
}

void pwmplay(){
    TA2CCR2=i;
    __delay_cycles(160000);
}
void pwmturnoff(){
    TA2CCR2=0;
}
void pwmadj(int target){
    static int pre=0;
    float temp=(float)target/(float)3500*512;
    int t=(int)temp;
    t=(pre+t)/2;
    pre=t;
    if(i>t){
        i-=5;

    }
    else{
        i+=5;
    }
    if(i>=512)i=512;
    if(i<=0)i=0;
}
