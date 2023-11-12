 #include <msp430.h>


/**
 * main.c
 */

#define T_PWM 10480 // 10 ms para o SMCLOCK (1 MHz +-)
#define SOBE_10 1048 // Usaremos isso para subir em 10% a potência (usanod pwm)
#define DBC 1000
#define TRUE    1
#define FALSE   0
#define ABERTA  1
#define FECHADA 0

void io_config(void);
void config_ta0(void);
int subir_10(void);
int descer_10(void);
void debounce(int valor);

int main(void)
{
      WDTCTL = WDTPW | WDTHOLD;     // stop watchdog timer
      io_config();
      config_ta0();
      while(TRUE)
      {
          if(subir_10() == TRUE)
          {
              if(TA0CCR1 < TA0CCR0) // Se a pot atual estiver abaixo da pot máxima (10480) ele prosseguirá o sobe_10
              {
                  TA0CCR1 += SOBE_10;
              }
          }
          if(descer_10() == TRUE)
          {
              if(TA0CCR1 > 0) // Pot atual tem que ser maior que 0
              {
                  TA0CCR1 -= SOBE_10;
              }
          }
      }
      
      
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

void config_ta0(void)
{
    TA0CTL = TASSEL_2 | MC_1;
    TA0CCTL1 = OUTMOD_6;
    TA0CCRT0 = T_PWM;
    TA0CCR1 = 5*SOBE_10;
    P1DIR |= BIT2;
    P1SEL |= BIT2;
}

int subir_10(void)
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

int descer_10(void)
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

void debounce(int valor)
{
    volatile int x;
    for (x = 0 ; x < valor ; x++);
}



