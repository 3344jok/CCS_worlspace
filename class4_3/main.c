#include <msp430.h> 
#include "ADC12.h"

unsigned int icnt;
void IO_Init(void)
{
    P8DIR |= BIT1;                          // ����P8.1��Ϊ���ģʽ  ����LED��
    P8OUT &= ~BIT1;                          // ѡ��P8.1Ϊ�����ʽ

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

    P3DIR |= BIT6;                          // ����P3.6��Ϊ���ģʽ  ���Ʒ�����
    P3OUT |= BIT6;                          // ѡ��P3.6Ϊ�����ʽ

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;
}

void  ClockInit()
{//����MCLK:16MHz,   SMCLK:8MHz,   ACLK:32KHz
    UCSCTL6 &= ~XT1OFF;          //����XT1
     P5SEL |= BIT2 + BIT3;             //XT2���Ź���ѡ��
     UCSCTL6 &= ~XT2OFF;          //��XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;       //DCOƵ�ʷ�Χ��28.2MHZ����
     UCSCTL2 = FLLD_5 + 1;          //D=16��N=1

     //n=8,FLLREFCLKʱ��ԴΪXT2CLK��
     //DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;
     //ACLK��ʱ��ԴΪDCOCLKDIV,MCLK\SMCLK��ʱ��ԴΪDCOCLK
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;
     //ACLK��DCOCLKDIV��32��Ƶ�õ���SMCLK��DCOCLK��2��Ƶ�õ�
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

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA0CCTL0 = CCIE;                        //�Ƚ����ж�ʹ��
    TA0CCR0  = 50000;                       //�Ƚ�ֵ��Ϊ50000���൱��50ms��ʱ����
    __enable_interrupt();

    unsigned int ivalue = 0;              //�����жϱ���
    unsigned int Micvalue = 0;              //�����жϱ���
    while(1)
    {
        ivalue = GetAD();               //û�������˲�
        Micvalue = Filter( );                 //�����˲�
        if(Micvalue>=2500){
            P1OUT |= BIT0;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt=0;
        }
       if(ivalue>=585)
       {
           P8OUT |= BIT1;
       }
       else{
           P8OUT &= ~BIT1;
       }
       if(ivalue>=1170)
       {
           P3OUT |= BIT7;
       }
       else{
           P3OUT &= ~BIT7;
       }
       if(ivalue>=1755)
       {
           P7OUT |= BIT4;
       }
       else{
           P7OUT &= ~BIT4;
       }
       if(ivalue>=2340)
       {
           P6OUT |= BIT3;
       }
       else{
           P6OUT &= ~BIT3;
       }
       if(ivalue>=2925)
       {
           P6OUT |= BIT4;
       }
       else{
           P6OUT &= ~BIT4;
       }
       if(ivalue>=3300)
       {
           P3OUT |= BIT5;
       }
       else{
           P3OUT &= ~BIT5;
       }
   }
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    icnt++;
    if(icnt>=1600)
    {//10s�ص�
      P1OUT &= ~BIT0;
      icnt=0;
    }
}