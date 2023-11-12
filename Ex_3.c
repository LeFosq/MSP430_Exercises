#include <msp430.h> 

void config_GPIO(void);
void debounce(int valor);
#define DBC 1000
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	while ((P1IN&BIT1) == BIT1)
	{
	    if ((P2IN&BIT1) == 0)
	    {
	        debounce(DBC);
	        P1OUT ^= BIT0;
	    }
	    else
	    {
	        
	    }
	}
	return 0;
}

void config_GPIO(void)
{
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
    
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
}

void debounce(int valor)
{
    volatile int x;
    for (x=0; x<valor; x++);
}