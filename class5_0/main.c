#include <msp430.h> 
#include "ADC12.h"
#include "pwm.h"
#include <math.h>
unsigned int icnt;
int LED_FLAG;
void IO_Init(void)
{
    //LEDIOinit
    {
        // LED初始化
        P1DIR |= BIT5; // P1.5输出
        P1OUT |= BIT5; // P1.5置1
        P2DIR |= BIT4; // P2.4输出
        P2OUT &= ~BIT4; // P2.4置0
        P2DIR |= BIT5; // P2.5输出
        P2SEL |= BIT5; // P2.5端口为外设，定时器TA2.2
    }

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

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P3DIR |= BIT6;                          // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;                          // 选中P3.6为输出方式

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;
}

void  ClockInit()
{//最终MCLK:16MHz,   SMCLK:8MHz,   ACLK:32KHz
    UCSCTL6 &= ~XT1OFF;          //启动XT1
     P5SEL |= BIT2 + BIT3;             //XT2引脚功能选择
     UCSCTL6 &= ~XT2OFF;          //打开XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;       //DCO频率范围在28.2MHZ以下
     UCSCTL2 = FLLD_5 + 1;          //D=16，N=1

     //n=8,FLLREFCLK时钟源为XT2CLK；
     //DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;
     //ACLK的时钟源为DCOCLKDIV,MCLK\SMCLK的时钟源为DCOCLK
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;
     //ACLK由DCOCLKDIV的32分频得到，SMCLK由DCOCLK的2分频得到
     UCSCTL5 = DIVA_5 +DIVS_1;
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

    InitAD();

    ClockInit();

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
    TA0CCTL0 = CCIE;                        //比较器中断使能
    TA0CCR0  = 50000;                       //比较值设为50000，相当于50ms的时间间隔

    TA2CTL = TASSEL_2 + TACLR + MC0;   //led时钟驱动
    TA2CCTL2=OUTMOD_7;
    TA2CCR0 = 512;

    __enable_interrupt();

    LED_FLAG=0;
    int ivalue = 0;              //设置判断变量
    unsigned int Micvalue = 0;              //设置判断变量
    while(1)
    {
        ivalue = Filter_light();               //光线信号
        ivalue+=4000;
        ivalue/=2;
        Micvalue = Filter( );                 //声音信号
        if(Micvalue>=2500){
            P1OUT |= BIT0;
            LED_FLAG=1;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt=0;
        }
       if(ivalue>=500)
       {
           P8OUT |= BIT1;
       }
       else{
           P8OUT &= ~BIT1;
       }
       if(ivalue>=1500)
       {
           P3OUT |= BIT7;
       }
       else{
           P3OUT &= ~BIT7;
       }
       if(ivalue>=2400)
       {
           P7OUT |= BIT4;
       }
       else{
           P7OUT &= ~BIT4;
       }
       if(ivalue>=2800)
       {
           P6OUT |= BIT3;
       }
       else{
           P6OUT &= ~BIT3;
       }
       if(ivalue>=3500)
       {
           P6OUT |= BIT4;
       }
       else{
           P6OUT &= ~BIT4;
       }
       if(ivalue>=3900)
       {
           P3OUT |= BIT5;
       }
       else{
           P3OUT &= ~BIT5;
       }
       if(LED_FLAG==1){
           pwmadj(abs(3500-(int)ivalue));
           pwmplay();
       }
   }
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    icnt++;
    if(icnt>=1600)
    {//10s关灯
        LED_FLAG=0;
        P1OUT &= ~BIT0;
        pwmturnoff();
      icnt=0;
    }
}
