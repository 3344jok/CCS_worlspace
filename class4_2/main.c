#include <msp430.h> 
#include "ADC12.h"

unsigned int icnt1,icnt2,icnt3,icnt4,icnt5,icnt6;

void IO_Init(void)
{
    P8DIR |= BIT1;                          // 设置P8.1口为输出模式  控制LED灯
    P8OUT &= ~BIT1;                          // 选中P8.1为输出方式

    P3DIR |= BIT7;
    P3OUT &= ~BIT7;

    P7DIR |= BIT4;
    P7OUT &= ~BIT4;

    P6DIR |= BIT3;
    P6OUT &= ~BIT3;

    P6DIR |= BIT4;
    P6OUT &= ~BIT4;

    P3DIR |= BIT5;
    P3OUT &= ~BIT5;

    P3DIR |= BIT6;                          // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;                          // 选中P3.6为输出方式

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;
}

int apInterface_Key( void )
{
   return 0;
}

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    IO_Init();

    ADInit(5);

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
    TA0CCTL0 = CCIE;                        //比较器中断使能
    TA0CCR0  = 50000;                       //比较值设为50000，相当于50ms的时间间隔
    __enable_interrupt();

    unsigned int ivalue = 0;              //设置判断变量
    while(1)
    {
          ivalue = GetAD();               //没有软件滤波
//        ivalue = Filter( );                 //软件滤波
        if(ivalue>=585)
        {
            P8OUT |= BIT1;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt1=0;
        }
        else{
            P8OUT &= ~BIT1;
        }
        if(ivalue>=1170)
        {
            P3OUT |= BIT7;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt2=0;
        }
        else{
            P3OUT &= ~BIT7;
        }
        if(ivalue>=1755)
        {
            P7OUT |= BIT4;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt3=0;
        }
        else{
            P7OUT &= ~BIT4;
        }
        if(ivalue>=2340)
        {
            P6OUT |= BIT3;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt4=0;
        }
        else{
            P6OUT &= ~BIT3;
        }
        if(ivalue>=2925)
        {
            P6OUT |= BIT4;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt5=0;
        }
        else{
            P6OUT &= ~BIT4;
        }
        if(ivalue>=3300)
        {
            P3OUT |= BIT5;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt6=0;
        }
        else{
            P3OUT &= ~BIT5;
        }
    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    icnt1++;
    icnt2++;
    icnt3++;
    icnt4++;
    icnt5++;
    icnt6++;
    if(icnt1>=2)
    {//10s关灯
       P8OUT &= ~BIT1;
       icnt1=0;
    }
    if(icnt2>=2)
    {//10s关灯
       P3OUT &= ~BIT7;
       icnt2=0;
    }
    if(icnt3>=2)
    {//10s关灯
       P7OUT &= ~BIT4;
       icnt3=0;
    }
    if(icnt4>=2)
    {//10s关灯
       P6OUT &= ~BIT3;
       icnt4=0;
    }
    if(icnt5>=2)
    {//10s关灯
       P6OUT &= ~BIT4;
       icnt5=0;
    }
    if(icnt6>=2)
    {//10s关灯
       P3OUT &= ~BIT5;
       icnt6=0;
    }
}
