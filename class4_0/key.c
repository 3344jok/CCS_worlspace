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

/************************IO口初始化********************************/
void IO_Init(void)
{
    P8DIR |= BIT1;              // 设置P8.1口为输出模式  控制LED灯
    P8OUT |= BIT1;  // 选中P8.1为输出方式

    P3DIR |= BIT6;              // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;  // 选中P3.6为输出方式

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
    if((P1IN&BIT2)!=BIT2)//通过IO口值得出按键按下信息
   {
        delay(50);  //延时去抖
        if((P1IN&BIT2)!=BIT2)   //通过IO口值得出按键按下信息
        {
    KeyFlag.S1=1;
        }
   }
   if((P1IN&BIT3)!=BIT3)//通过IO口值得出按键按下信息
   {
        delay(50);   //延时去抖
        if((P1IN&BIT3)!=BIT3) //通过IO口值得出按键按下信息
        {
                KeyFlag.S2=1;
        }
   }
   if((P2IN&BIT3)!=BIT3) //通过IO口值得出按键按下信息
  {
        delay(50);   //延时去抖
        if((P2IN&BIT3)!=BIT3)           //通过IO口值得出按键按下信息
        {
                KeyFlag.S3=1;
        }
  }
  if((P2IN&BIT6)!=BIT6) //通过IO口值得出按键按下信息
  {
         delay(50);//延时去抖
         if((P2IN&BIT6)!=BIT6)          //通过IO口值得出按键按下信息
         {
               KeyFlag.S4=1;
         }
   }
}



