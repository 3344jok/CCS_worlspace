#include <msp430.h> 
#include "ADC12.h"

unsigned int icnt1,icnt2,icnt3,icnt4,icnt5,icnt6;

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

    P3DIR |= BIT6;                          // ����P3.6��Ϊ���ģʽ  ���Ʒ�����
    P3OUT |= BIT6;                          // ѡ��P3.6Ϊ�����ʽ

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

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA0CCTL0 = CCIE;                        //�Ƚ����ж�ʹ��
    TA0CCR0  = 50000;                       //�Ƚ�ֵ��Ϊ50000���൱��50ms��ʱ����
    __enable_interrupt();

    unsigned int ivalue = 0;              //�����жϱ���
    while(1)
    {
          ivalue = GetAD();               //û������˲�
//        ivalue = Filter( );                 //����˲�
        if(ivalue>=585)
        {
            P8OUT |= BIT1;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt1=0;
        }
        else{
            P8OUT &= ~BIT1;
        }
        if(ivalue>=1170)
        {
            P3OUT |= BIT7;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt2=0;
        }
        else{
            P3OUT &= ~BIT7;
        }
        if(ivalue>=1755)
        {
            P7OUT |= BIT4;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt3=0;
        }
        else{
            P7OUT &= ~BIT4;
        }
        if(ivalue>=2340)
        {
            P6OUT |= BIT3;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt4=0;
        }
        else{
            P6OUT &= ~BIT3;
        }
        if(ivalue>=2925)
        {
            P6OUT |= BIT4;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt5=0;
        }
        else{
            P6OUT &= ~BIT4;
        }
        if(ivalue>=3300)
        {
            P3OUT |= BIT5;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
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
    {//10s�ص�
       P8OUT &= ~BIT1;
       icnt1=0;
    }
    if(icnt2>=2)
    {//10s�ص�
       P3OUT &= ~BIT7;
       icnt2=0;
    }
    if(icnt3>=2)
    {//10s�ص�
       P7OUT &= ~BIT4;
       icnt3=0;
    }
    if(icnt4>=2)
    {//10s�ص�
       P6OUT &= ~BIT3;
       icnt4=0;
    }
    if(icnt5>=2)
    {//10s�ص�
       P6OUT &= ~BIT4;
       icnt5=0;
    }
    if(icnt6>=2)
    {//10s�ص�
       P3OUT &= ~BIT5;
       icnt6=0;
    }
}
