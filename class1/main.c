#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
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
        P7OUT^=BIT4;
        P2IFG&=~BIT3;
    }
}
