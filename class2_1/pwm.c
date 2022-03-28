/*
 * pwm.c
 *
 *  Created on: 2022年3月7日
 *      Author: z
 */
#include "pwm.h"
void pwmout(){
    // stop watchdog timer
//    WDTCTL = WDTPW | WDTHOLD;

    // 选择时钟ACLK, 清除 TAR，增计数
    TA0CTL = TASSEL_2 + TACLR + MC0;
    TA0CCR0 = 512;   // PWM周期
    TA0CCTL1 = OUTMOD_7 ;// 输出模式7
    TA0CCR1 = 0;  //占空比90%
    TA0CCTL2 = OUTMOD_7; // 输出模式7;
    P1DIR |= BIT2;    // P1.2 方向为输出
    P1SEL |= BIT2;   // P1.2端口为外设，定时器TA0.1
    P1DIR |= BIT3;    // P1.3 方向为输出
    P1SEL |= BIT3;   // P1.3端口为外设，定时器TA0.2
    int i=0;
    while(1){
        for(i=0;i<512;i++){
            TA0CCR2 = i;  //占空比10%
            __delay_cycles(152000);
        }
        for(i=512;i>=0;i--){
            TA0CCR2 = i;  //占空比10%
            __delay_cycles(152000);
        }
    }





}


