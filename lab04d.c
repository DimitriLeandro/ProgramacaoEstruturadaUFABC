#include <stdio.h>

void verificarEquilibrio(int pe, int de, int pd, int dd);
int contarPeso();
int equilibrado = 1;
int pesoTotal = 0;

int main(void) {
  int pe, de, pd, dd;

  contarPeso();

  if(equilibrado == 1){
    printf("Mobile equilibrado\n");
  }else{
    printf("Mobile desequilibrado\n");
  }
  printf("Peso total: %d\n", pesoTotal);

  return 0;
}

void verificarEquilibrio(int pe, int de, int pd, int dd){
  if((pe * de) != (pd * dd)){
    equilibrado = 0;
  }
}

int contarPeso(){
  int pe, de, pd, dd;

  scanf("%d %d %d %d", &pe, &de, &pd, &dd);

  pesoTotal += pe + pd;

  if(pe == 0){
    pe = contarPeso();
  }
  if(pd == 0){
    pd = contarPeso();
  } 
  
  verificarEquilibrio(pe, de, pd, dd);
  return pe + pd;
}