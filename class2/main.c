#include <msp430.h> 

void ClockInit()
{//最终MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
     UCSCTL6 &= ~XT1OFF;       //启动XT1
     P5SEL |= BIT2 + BIT3;     //XT2引脚功能选择
     UCSCTL6 &= ~XT2OFF;       //打开XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;  //DCO频率范围在28.2MHZ以下
     UCSCTL2 = FLLD_5 + 1;       //D=16，N=1

     //n=8,FLLREFCLK时钟源为XT2CLK；
     //DCOCLK=D*(N+1)*(FLLREFCLK/n);
     //DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;

     //ACLK的时钟源为DCOCLKDIV,
     //MCLK\SMCLK的时钟源为DCOCLK
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;

     //ACLK由DCOCLKDIV的32分频得到，
     //SMCLK由DCOCLK的2分频得到
     UCSCTL5 = DIVA_5 +DIVS_1;
}
/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    ClockInit();
    //LED
    P1DIR|=BIT5;
    P1OUT|=BIT5;
    P2DIR|=BIT4;
    P2OUT&=~ BIT4;
    P2DIR|=BIT5;
    P2OUT|=BIT5;
    //s2
    P3DIR|=BIT7;
    P3OUT&=~ BIT7;
    P1REN|=BIT3;
    P1OUT|=BIT3;
    P1IE|=BIT3;
    P1IES|=BIT3;
    P1IFG&=~BIT3;
    //s1
    P8DIR|=BIT1;
    P8OUT&=~ BIT1;
    P1REN|=BIT2;
    P1OUT|=BIT2;
    P1IE|=BIT2;
    P1IES|=BIT2;
    P1IFG&=~BIT2;
    //s3
    P7DIR|=BIT4;
    P7OUT&=~ BIT4;
    P2REN|=BIT3;
    P2OUT|=BIT3;
    P2IE|=BIT3;
    P2IES|=BIT3;
    P2IFG&=~BIT3;
    _enable_interrupt();
    while(1){
        P2OUT^=BIT4;
        __delay_cycles(16000000);
    }

    return 0;
}
#pragma vector=PORT1_VECTOR

__interrupt void PORT1 (void)
{
    if(P1IFG&BIT3){
        P3OUT^=BIT7;
        P1IFG&=~BIT3;
    }
    if(P1IFG&BIT2){
        P8OUT^=BIT1;
        P1IFG&=~BIT2;
    }
}
#pragma vector=PORT2_VECTOR

__interrupt void PORT2 (void)
{
    if(P2IFG&BIT3){

        P2OUT^=BIT4;

//        P7OUT^=BIT4;
        P2IFG&=~BIT3;
    }
}
