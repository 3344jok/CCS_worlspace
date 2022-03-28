/*
 * AD.c
 *
 *  Created on: 2022年3月21日
 *      Author: z
 */
#include "AD.h"


void AD_Init()
{
    ADC12CTL0 |= ADC12MSC;                      //自动循环采样转换
    ADC12CTL0 |= ADC12ON;                        //启动ADC12模块
    ADC12CTL1 |= ADC12CONSEQ1 ;           //选择单通道循环采样转换
    ADC12CTL1 |= ADC12SHP;                      //脉冲采样模式
    ADC12MCTL0 |= ADC12INCH_5;            //选择通道5，连接拨码电位器
    ADC12CTL0 |= ADC12ENC;
}

