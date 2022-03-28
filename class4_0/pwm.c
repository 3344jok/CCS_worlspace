/*
 * pwm.c
 *
 *  Created on: 2022��3��7��
 *      Author: z
 */
#include "pwm.h"
void pwmout(){
    // stop watchdog timer
//    WDTCTL = WDTPW | WDTHOLD;

    // ѡ��ʱ��ACLK, ��� TAR��������
    TA0CTL = TASSEL_2 + TACLR + MC0;
    TA0CCR0 = 512;   // PWM����
    TA0CCTL1 = OUTMOD_7 ;// ���ģʽ7
    TA0CCR1 = 0;  //ռ�ձ�90%
    TA0CCTL2 = OUTMOD_7; // ���ģʽ7;
    P1DIR |= BIT2;    // P1.2 ����Ϊ���
    P1SEL |= BIT2;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
    P1DIR |= BIT3;    // P1.3 ����Ϊ���
    P1SEL |= BIT3;   // P1.3�˿�Ϊ���裬��ʱ��TA0.2
    int i=0;
    while(1){
        for(i=0;i<512;i++){
            TA0CCR2 = i;  //ռ�ձ�10%
            __delay_cycles(152000);
        }
        for(i=512;i>=0;i--){
            TA0CCR2 = i;  //ռ�ձ�10%
            __delay_cycles(152000);
        }
    }





}


