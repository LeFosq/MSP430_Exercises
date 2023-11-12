#include <msp430.h> 

void config_GPIO(void);
//void debounce(int valor);
void delay(unsigned int ms);
#define delay_n 12500000
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	while (1)
	{
	    P1OUT ^= ~BIT0;
	    delay(delay_n);
	}
	return 0;
}

void config_GPIO(void)
{
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
}

//void debounce(int valor)
//{
 //   volatile int x;
 //   for (x=0; x<valor; x++);
//}

void delay(unsigned int ms)
{
    unsigned int i;
    for (i = 0; i < ms; i++);
}
