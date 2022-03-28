#include <msp430.h> 
#include "key.h"
#include "pwm.h"
unsigned int i=0;
void main(void)
{
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer



    IO_Init();

    //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA0CTL |= MC_1 + TASSEL_2 + TACLR;
    TA0CCTL0 = CCIE;                //�Ƚ����ж�ʹ��
    TA0CCR0  = 50000;               //�Ƚ�ֵ��Ϊ50000���൱��50ms��ʱ����
    while(1)
    {
        ScanKey();                          //�ӿ�
          if(KeyFlag.S1==1)
          {
              KeyFlag.S1=0;         //�����ӿ�
              P8OUT |= BIT1;          //�γ�����Ч��
              P3OUT |= BIT6;      //�γ�����Ч��
              i=0;
              __disable_interrupt();
          }
          else{

              __enable_interrupt();
          }
//          if(KeyFlag.S2==1)
//        {
//            KeyFlag.S2=0;
//
//
//        }
    }
}
/************************��ʱ���жϺ���********************************/
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    i++;
    if(i==100)
   {
        P8OUT &= ~BIT1;          //�ر�����Ч��
        P3OUT &= ~BIT6;      //�رշ�����
        i=0;
   }
}


