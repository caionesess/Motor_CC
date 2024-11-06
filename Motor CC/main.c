
#include "io430.h"
#include "teclado.h"
#define CICLOS	999	                // Define um per�odo de 1000 pulsos de clock (F=1kHZ)

char teclas;

void funcionalidades (void)
{
 teclas=teclado();
    
    switch(teclas)
    {
      case('1'):                        // Aumenta velocidade anti-hor�rio
        if(TA0CCR1 > 0)
	TA0CCR1--;                      // Decrementa o CT
        break;
        
      case('2'):                        // Ciclo de trabalho 50%
        TA0CCR1= (CICLOS/2);            // Limite da contagem a cada CICLO de clock (DT=50%)
        break;
        
      case('3'):                        // Aumenta velocidade hor�rio
        if(TA0CCR1 < TA0CCR0-1)
	TA0CCR1++;                      // Incrementa o CT
        break;
          
      case('5'):                        // Motor parado (com ajuste de offset do driver)
        TA0CCR1= (CICLOS/2)-16;         // Limite da contagem a cada CICLO de clock (DT=50%)
        break;
            
      case('7'):                        // Aciona o motor CC no sentido hor�rio com velocidade constante
        TA0CCR1= (CICLOS/2)+300;        // de 10% da velocidade m�xima
        break;
    }
}

void main(void)
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 &= ~XT2OFF;
  BCSCTL2 |= SELS;			//Define XT2 como fonte de clock do SMCLK
  
  // Configura��o do Timer_A
  TA0R=0;                     	        //Reseta contador 
  TACTL = TASSEL1 +          	        // Fonte do clock: SMCLK ( 4MHz )
    ID1 +		                // Divide SMCLK/4 = 1MHz
      MC_1;               	        // Modo de contagem: crescente cont�nua
  
  // Bloco Capture/Compare 0
  TA0CCR0=CICLOS;            	        // Per�odo da modula��o
  
  // Bloco Capture/Compare 1
  TA0CCR1=CICLOS/2;            	        // Limite da contagem a cada CICLO de clock (DT=50%)
  TA0CCTL1 = OUTMOD_7;         	        // Modo de opera��o 7 Reset/set
  P1DIR |= BIT2; 		        // Define P1.2 como sa�da
  P1SEL |= BIT2; 			// Habilita fun��o especial em P1.2 (TA1)- PWM
  
  // Configura��o da porta
  P2DIR &= ~(BIT0+BIT1);
  
  configura_teclado();
  
  while(1)
  {
    funcionalidades();
  }
}