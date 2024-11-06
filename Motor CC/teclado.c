#include "io430.h"

#define COLUNA_DIR  P2DIR
#define COLUNAS     P2IN
#define LINHA_DIR   P3DIR
#define LINHAS      P3OUT
#define TEMPO       3000

const char TAB_TEC[]={0X00,0X33,0X32,0X31,0X36,0X35,0X34,0X39,0X38,0X37,0X45,0X30,0X41};
const char TAB_LIN[]={0X01,0X02,0X04,0X08,0X00};

const char *APT_TEC;
const char *APT_LIN;
unsigned char tecla;
/*---------------------------------------------------------------------------
Função: TempoConfiguravel
Descrição: Carrega um contador e realiza decrementos sucessivos até zerar.
Entrada: unsigned int - período da temporização
Saída: -
---------------------------------------------------------------------------*/
void TempoConfiguravel(unsigned int periodo)
{
unsigned int cont; // Variavel auxiliar para contagem
cont = periodo; // contagem de tempo
while (cont != 0)
cont--;
}

void configura_teclado(void)
{
LINHA_DIR|=0X0F;      // Define as linhas como saída
COLUNA_DIR&=0XF8;     // Define as colunas como entrada
}
/*------------------------------------------------------------------------------
Nome:       teclado
Descrição:  Função para ler a entrada do teclado matricial.
Entrada:         -
Saída:           -
------------------------------------------------------------------------------*/
 unsigned char teclado(void)
 {
   
    tecla=0x00;
    LINHAS=0XF;
    APT_TEC=TAB_TEC;
    APT_LIN=TAB_LIN;
    if((COLUNAS&0x07)==0x00)
    {
       tecla=*APT_TEC;
    }
    TempoConfiguravel(TEMPO);  
    LINHAS=*APT_LIN;
    while(((COLUNAS&0X07)==0X00)&&(*APT_LIN!=0X00))
    {
      APT_TEC=APT_TEC+3;
      APT_LIN=APT_LIN+1;
      LINHAS=*APT_LIN;
    }

      if(APT_LIN==0X00)
      {
        APT_TEC=TAB_TEC;
      }
      switch(COLUNAS&0x07){
        case(0x01):
        {
          APT_TEC=APT_TEC+0X01;
          break;
        }
        case(0x02):
        {
          APT_TEC=APT_TEC+0X02;
          break;
        }
        case(0x04):
        {
          APT_TEC=APT_TEC+0X03;
          break;
        }
      default:
        APT_TEC=TAB_TEC;
    }
    tecla=*APT_TEC;
    return(tecla);
 }
 