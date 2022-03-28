#include <msp430.h> 
#include <key.h>
#include <pwm.h>
void ClockInit()
{//����MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
     UCSCTL6 &= ~XT1OFF;       //����XT1
     P5SEL |= BIT2 + BIT3;     //XT2���Ź���ѡ��
     UCSCTL6 &= ~XT2OFF;       //��XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;  //DCOƵ�ʷ�Χ��28.2MHZ����
     UCSCTL2 = FLLD_5 + 1;       //D=16��N=1

     //n=8,FLLREFCLKʱ��ԴΪXT2CLK��
     //DCOCLK=D*(N+1)*(FLLREFCLK/n);
     //DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;

     //ACLK��ʱ��ԴΪDCOCLKDIV,
     //MCLK\SMCLK��ʱ��ԴΪDCOCLK
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;

     //ACLK��DCOCLKDIV��32��Ƶ�õ���
     //SMCLK��DCOCLK��2��Ƶ�õ�
     UCSCTL5 = DIVA_5 +DIVS_1;
}
/**
 * main.c
 */
int main(void)
{
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;
    ClockInit();
    IO_Init();
    // ѡ��ʱ��ACLK, ��� TAR��������
    TA0CTL = TASSEL_2 + TACLR + MC0;

    TA0CCR0 = 512;   // PWM����

    TA0CCTL1 = OUTMOD_7 ;// ���ģʽ7

    TA0CCR1 = 0;  //ռ�ձ�90%
    //LEDIOinit
    {
        P1DIR|=BIT5;
        P1OUT|=BIT5;
        P1DIR |= BIT2;    // P1.2 ����Ϊ���
        P1SEL |= BIT2;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
        P2DIR|=BIT5;
        P2OUT|=BIT5;
    }
    while(1){
        ScanKey();                          //ɨ�谴������
          if(KeyFlag.S3==1)
          {
              KeyFlag.S3=0;
              pwmadd();
          }
          if(KeyFlag.S4==1)
        {
            KeyFlag.S4=0;
            pwmdecr();
        }
          pwmplay();
    }
}
