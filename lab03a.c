#include <stdio.h>

int main(void) {
  
  /* a variavel indicador diz se o golpe esta sendo aplicado ou sofrido 1->aplicando -1->sofrendo */
  int roundsKen = 0, roundsRyu = 0, golpe, indicador = 1, somaRound = 0;

  do{
    scanf("%d", &golpe);
    if(golpe == 0 || (indicador == -1 && golpe > 0)){
      if(somaRound > 0){
          roundsRyu++;
      }else{
        roundsKen++;
      }
      somaRound = golpe;
      indicador = 1;
    }else{
      if((indicador == 1 && golpe > 0) || (indicador == -1 && golpe < 0)){
        somaRound += golpe;        
      }else{
        somaRound += golpe;
        indicador = -1;       
      }
    }
  }while(golpe != 0);

  if(roundsKen > roundsRyu){
    printf("Ken venceu\n");
  }else if(roundsRyu > roundsKen){
    printf("Ryu venceu\n");
  }else{
    printf("empatou\n");
  }

  return 0;
}