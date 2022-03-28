/*
 * key.c
 *
 *  Created on:
 *      Author:
 */
#include "key.h"
#include <msp430.h>

StrKeyFlag KeyFlag;
void delay(uint16 t)
{
    uint16 i,j,k;

    for(j=t;j>0;j--)
        for(i=250;i>0;i--)
            k=0;
}

/************************IO�ڳ�ʼ��********************************/
void IO_Init(void)
{
    P8DIR |= BIT1;              // ����P8.1��Ϊ���ģʽ  ����LED��
    P8OUT |= BIT1;  // ѡ��P8.1Ϊ�����ʽ

    P3DIR |= BIT6;              // ����P3.6��Ϊ���ģʽ  ���Ʒ�����
    P3OUT |= BIT6;  // ѡ��P3.6Ϊ�����ʽ

    P2DIR |= BIT2;
    P2OUT &=~ BIT2;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;
}

void ScanKey(void)
{
    if((P1IN&BIT2)!=BIT2)//ͨ��IO��ֵ�ó�����������Ϣ
   {
        delay(50);  //��ʱȥ��
        if((P1IN&BIT2)!=BIT2)   //ͨ��IO��ֵ�ó�����������Ϣ
        {
    KeyFlag.S1=1;
        }
   }
   if((P1IN&BIT3)!=BIT3)//ͨ��IO��ֵ�ó�����������Ϣ
   {
        delay(50);   //��ʱȥ��
        if((P1IN&BIT3)!=BIT3) //ͨ��IO��ֵ�ó�����������Ϣ
        {
                KeyFlag.S2=1;
        }
   }
   if((P2IN&BIT3)!=BIT3) //ͨ��IO��ֵ�ó�����������Ϣ
  {
        delay(50);   //��ʱȥ��
        if((P2IN&BIT3)!=BIT3)           //ͨ��IO��ֵ�ó�����������Ϣ
        {
                KeyFlag.S3=1;
        }
  }
  if((P2IN&BIT6)!=BIT6) //ͨ��IO��ֵ�ó�����������Ϣ
  {
         delay(50);//��ʱȥ��
         if((P2IN&BIT6)!=BIT6)          //ͨ��IO��ֵ�ó�����������Ϣ
         {
               KeyFlag.S4=1;
         }
   }
}



