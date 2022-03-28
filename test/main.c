#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P8DIR|=BIT1;
	P8OUT&=~ BIT1;
	P1REN|=BIT2;
	P1OUT|=BIT2;
	   P1IE|=BIT2;
	   P1IES|=BIT2;
	   P1IFG&=~BIT2;
	   _enable_interrupt();
	while(1){

	}
	
	return 0;
}
#pragma vector=PORT1_VECTOR

__interrupt void PORT1 (void)
{
    if(P1IFG&BIT2){
        P8OUT^=BIT1;
        P1IFG&=~BIT2;
    }
}
