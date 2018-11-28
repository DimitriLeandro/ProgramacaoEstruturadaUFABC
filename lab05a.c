#include <stdio.h>

int main(void) {
  int tamanhoRNA, tamanhoOligo, contRNA, contOligo, silencia;
  scanf("%d %d", &tamanhoRNA, &tamanhoOligo);  
  char rna[tamanhoRNA], oligo[tamanhoOligo], oligoEsperado;

  scanf("%s", rna);
  scanf("%s", oligo);

  for(contRNA = 0; contRNA <= (tamanhoRNA - tamanhoOligo); contRNA++){
    silencia = contRNA;
    for(contOligo = (tamanhoOligo - 1); contOligo >= 0; contOligo--){
      if(rna[contRNA + ((tamanhoOligo - 1) - contOligo)] == 'U'){
        oligoEsperado = 'A';
      }else if(rna[contRNA + ((tamanhoOligo - 1) - contOligo)] == 'C'){
        oligoEsperado = 'G';
      }else if(rna[contRNA + ((tamanhoOligo - 1) - contOligo)] == 'A'){
        oligoEsperado = 'U';
      }else{
        oligoEsperado = 'C';
      }

      if(oligoEsperado != oligo[contOligo]){
        silencia = -1;
        continue;
      }
    }
    if(silencia != -1){
      break;
    }
  }

  if(silencia != -1){
    printf("Silenciado em %d\n", (silencia + 1));
  }else{
    printf("Nao silenciado\n");
  }

  return 0;
}