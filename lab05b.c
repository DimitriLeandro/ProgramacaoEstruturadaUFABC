#include <stdio.h>

void explodir(int linha, int coluna, int raio);
void printarMatriz();

char matriz[51][51];
int L, C;

int main(void) {
  /* declaracao de variaveis */
  int linha, coluna, i;

  /* lendo as variaveis */
  scanf("%d %d %d %d", &L, &C, &linha, &coluna);

  /* colocando x e y nas proporcoes da matriz */
  linha--;
  coluna--;

  /* lendo a matriz (. -> tem nada)(n -> tem bomba de raio n) */
  for(i = 0; i < L; i++){
    scanf("%s", matriz[i]);
  }

  /* explodindo a primeira bomba */
  explodir(linha, coluna, (matriz[linha][coluna] - '0'));  

  printarMatriz();

  return 0;
}

void printarMatriz(){
  int i, j;
  /* printando a matriz */
  for(i = 0; i < L; i++){
    for(j = 0; j < C; j++){
      printf("%c", matriz[i][j]);
    }
    printf("\n");
  }
}

void explodir(int linha, int coluna, int raio){
  /* declarando variaveis */
  int i, j;  

  /* onde comeca e onde termina a micromatriz que ira explodir */
  int linhaInicio = linha - raio;
  int linhaFim = linha + raio;
  int colunaInicio = coluna - raio;
  int colunaFim = coluna + raio;

  /* verificando se as bordas ainda estao dentro da matriz original */
  if(linhaInicio < 0){
    linhaInicio = 0;
  }
  if(linhaFim >= L){
    linhaFim = L - 1;
  }
  if(colunaInicio < 0){
    colunaInicio = 0;
  }
  if(colunaFim >= C){
    colunaFim = C - 1;
  }

  /* explodindo cada casa da micromatriz */
  for(i = linhaInicio; i <= linhaFim; i++){
    for(j = colunaInicio; j <= colunaFim; j++){
      if(i == linha && j == coluna){
        matriz[i][j] = 'B';
      }else{
        if(matriz[i][j] == '.'){
          matriz[i][j] = 'x';
        }else if(matriz[i][j] == 'x' || matriz[i][j] == 'B'){
          continue;
        }else{
          explodir(i, j, (matriz[i][j] - '0'));
        }
      }      
    }
  }
}
