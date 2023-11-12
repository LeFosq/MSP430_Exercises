#include <msp430.h>


/**
 * main.c
 */
#define TRUE    1
#define FALSE   0
#define ABERTA  1
#define FECHADA 0
#define DBC     1000

int monit_c1(void);
int monit_c2(void);
void leds(int ct);
void io_config(void);
void debounce(int valor);

int main(void)
{
    int cont = 0;
      WDTCTL = WDTPW | WDTHOLD;     // stop watchdog timer
      io_config();
      while ((P2IN & BIT1) == BIT1 || (P1IN & BIT1) == BIT1)
      {
          if (monit_c1() == TRUE) cont++;
          if (monit_c2() == TRUE) cont--;
          leds(cont);
      }
      return 0;
}

void io_config(void)
{
    P2DIR  &=   ~BIT1;
    P2REN  |=   BIT1;
    P2OUT  |=   BIT1;
    P1DIR  &=   ~BIT1;
    P1REN  |=   BIT1;
    P1OUT  |=   BIT1;
    P1DIR  |=   BIT0;
    P1OUT  &=   ~BIT0;
    P4DIR  |=   BIT7;
    P4OUT  &=   ~BIT7;
}

void leds(int ct)
{
    switch(ct & 3)
    {
    case 0: P1OUT &= ~BIT0; P4OUT &= ~BIT7; break;
    case 1: P1OUT &= ~BIT0; P4OUT |= BIT7;  break;
    case 2: P1OUT |= BIT0; P4OUT &= ~BIT7;  break;
    case 3: P1OUT |= BIT0; P4OUT |= BIT7;   break;
    }
}

void debounce(int valor)
{
    volatile int x;
    for (x = 0 ; x < valor ; x++);
}

int monit_c1(void)
{
    static int ps1 = ABERTA; // chave passada
    if ((P2IN&BIT1) == 0)   // se P2.1 estiver pressionada
    {
        if (ps1 == ABERTA)
        {
            debounce(DBC);
            ps1 = FECHADA;
            return TRUE;
        }

    }
    else
    {
        if (ps1 == FECHADA)
        {
            debounce(DBC);
            ps1 = ABERTA;
            return FALSE;
        }
    }
    return FALSE;
}
int monit_c2(void)
{
    static int ps2 = ABERTA; // chave passada
    if ((P1IN&BIT1) == 0)   // se P1.1 estiver pressionada
        {
           if (ps2 == ABERTA)
           {
               debounce(DBC);
               ps2 = FECHADA;
               return TRUE;
           }

        }
        else
        {
            if (ps2 == FECHADA)
            {
                debounce(DBC);
                ps2 = ABERTA;
                return FALSE;
            }
        }
        return FALSE;
}
