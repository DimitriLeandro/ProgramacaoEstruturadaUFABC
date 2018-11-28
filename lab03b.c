#include <stdio.h>

int main(void) {
  
  int raio = 0, x = 0, y = 0, foreward = 0;
  char comando = 'F', direcao = 'N';

  scanf(" %d", &raio);

  do{
    scanf(" %c", &comando); /* MANTER O ESPACO ANTES DO %C */
    if(comando != 'X'){
      /* SEGUINDO EM FRENTE */
      if(comando == 'F'){ 
        scanf(" %d", &foreward);
        if(direcao == 'N'){
          y += foreward;
        }else if(direcao == 'S'){
          y -= foreward;
        }else if(direcao == 'E'){
          x += foreward;
        }else{
          x -= foreward;
        }
      }
      /* VIRANDO PARA A DIREITA */
      else if(comando == 'R'){ 
        if(direcao == 'N'){
          direcao = 'E';
        }else if(direcao == 'S'){
          direcao = 'W';
        }else if(direcao == 'E'){
          direcao = 'S';
        }else{
          direcao = 'N';
        }
      }
      /* VIRANDO PARA A ESQUERDA */
      else{ 
        if(direcao == 'N'){
          direcao = 'W';
        }else if(direcao == 'S'){
          direcao = 'E';
        }else if(direcao == 'E'){
          direcao = 'N';
        }else{
          direcao = 'S';
        }
      }

      /* VERIFICANDO SE ELE SAIU DO RAIO */
      if(raio * raio < x*x + y*y){
        comando = 'X';
      }
    }
  }while(comando != 'X'); 

  /* PRINTANDO O RESULTADO */
  if(x >= 0){
    printf("%dE ", x);
  } else {
    printf("%dW ", -x);
  }

  if(y >= 0){
    printf("%dN\n", y);
  } else {
    printf("%dS\n", -y);
  }

  return 0;
}