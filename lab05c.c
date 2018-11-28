#include <stdio.h>

void intercala(int v1[], int n1, int v2[], int n2, int v3[]);

int main(void) {

  int tamanhoV1, tamanhoV2, i;

  scanf("%d", &tamanhoV1);
  int v1[tamanhoV1];
  for(i = 0; i < tamanhoV1; i++){
    scanf("%d", &v1[i]);
  }

  scanf("%d", &tamanhoV2);
  int v2[tamanhoV2];
  for(i = 0; i < tamanhoV2; i++){
    scanf("%d", &v2[i]);
  }

  int v3[tamanhoV1 + tamanhoV2];

  intercala(v1, tamanhoV1, v2, tamanhoV2, v3);

  return 0;
}

void intercala(int v1[], int n1, int v2[], int n2, int v3[]){
  int i, j, k, aux;
  
  for(i = 0; i < (n1 + n2); i++){
    if(i < n1){
      v3[i] = v1[i];
    }else{
      v3[i] = v2[i - n1];
    }

    for(j = 0; j <= i - 1; j++){
      for(k = j + 1; k <= i; k++){
        if(v3[j] > v3[k]){
          aux = v3[j];
          v3[j] = v3[k];
          v3[k] = aux;
        }
      }
    }

  }

  for(i = 0; i < n1 + n2; i++){
    if(i == (n1 + n2 - 1)){
      printf("%d\n", v3[i]);
    }else{
      printf("%d ", v3[i]);
    }    
  }

}