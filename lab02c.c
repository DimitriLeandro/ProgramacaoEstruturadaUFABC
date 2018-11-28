#include <stdio.h>

/* O progrma deve ler uma data e informar qual e o dia da semana. Alem disso, o programa deve validar as datas para informar se uma data e invalida */

int main(void) {
  
  int dia, mes, ano, w, x, y;

  scanf("%d", &dia);
  scanf("%d", &mes);
  scanf("%d", &ano);

  /* validando a data */
  if(ano < 0 || dia > 31 || dia < 1 || mes > 12 || mes < 1 || (mes == 2 && dia > 28) || (mes == 4 && dia > 30) || (mes == 6 && dia > 30) || (mes == 9 && dia > 30) || (mes == 11 && dia > 30)){
    printf("invalida\n");
  }else{
    switch(mes){
      case 1:
        x = 28;
        break;
      case 2:
        x = 31;
        break;
      case 3:
        x = 2;
        break;
      case 4:
        x = 5;
        break;
      case 5:
        x = 7;
        break;
      case 6:
        x = 10;
        break;
      case 7:
        x = 12;
        break;
      case 8:
        x = 15;
        break;
      case 9:
        x = 18;
        break;
      case 10:
        x = 20;
        break;
      case 11:
        x = 23;
        break;
      case 12:
        x = 25;
        break;
    }

    if(mes == 1 || mes == 2){
      ano--;
    }

    y = 5 * (ano % 4) + 4 * (ano % 100) + 6 * (ano % 400);

    w = (dia + x + y) % 7;

    switch(w){
      case 0:
        printf("domingo\n");
        break;
      case 1:
        printf("segunda\n");
        break;
      case 2:
        printf("terca\n");
        break;
      case 3:
        printf("quarta\n");
        break;
      case 4:
        printf("quinta\n");
        break;
      case 5:
        printf("sexta\n");
        break;
      case 6:
        printf("sabado\n");
        break;
    }
  } 

  return 0;
}