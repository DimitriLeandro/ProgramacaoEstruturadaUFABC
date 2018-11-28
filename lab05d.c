/* lab05d: Processamento de imagens
 * Autor: Dimitri Leandro de Oliveira Silva
 * RA: 11201720576
 */

#include <stdio.h>
#include <string.h>

/* Definindo tamanho maximo das imagens */
#define MAX_TAM 400

/* funcoes prontas */
int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV,int *F, double *Px, double *Py);
void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV);

/* funcoes que devem ser elaboradas para o exercicio */
void negativo(int img[][MAX_TAM], int W, int H, int MaxV);
void rotacao180(int img[][MAX_TAM], int W, int H);
void detectaBorda(int img[][MAX_TAM], int W, int H, int MaxV);
void cisalhamento(int img[][MAX_TAM], int W, int H, double Px, double Py);

int main() {
    /* Matriz que armazena os pixels da imagem */
    int img[MAX_TAM][MAX_TAM]; 
    /* Atributos da imagem */
    int W, H, MaxV;
    /* Identificador do filtro a ser utilizado */
    int F;
    /* Parâmetro a ser passado para o cisalhamento */
    double Px, Py;

    /* Le a imagem */
    if (ler_pgm(img, &W, &H, &MaxV, &F, &Px, &Py) != 1) {
        printf("Error: nao foi possivel ler a imagem\n");
        return 0;
    }
 
    /* Seleciona o filtro */
    switch (F) {
        case 1:
            negativo(img, W, H, MaxV);
            break;
        case 2:
            rotacao180(img, W, H);
            break;
        case 3:
            detectaBorda(img, W, H, MaxV);
            break;
        case 4:
            cisalhamento(img, W, H, Px, Py);
            break;
    }

    /* Escreve a imagem */
    escrever_pgm(img, W, H, MaxV);

    return 0;
}

int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV, int *F, double *Px, double *Py) {
    char nome_formato[3];
    char c;
    int i,j;

    /* Le o formato da imagem. P2 indica o formato PGM */
    scanf("%s ", nome_formato);
    if (strcmp(nome_formato, "P2") != 0){
      return 0;
    }

    /* Le o '#', que indica um comentario, e os numeros indicando
    * o filtro e o parametro, se houver */
    scanf("%[#]c", &c);
    scanf("%d", F);
    if (*F == 4) {
      scanf("%lf %lf", Px, Py);
    } 
 
    /* Le dimensoes e intensidade maxima da imagem */
    scanf("%d", W);
    scanf("%d", H);
    scanf("%d", MaxV);
 
    /* Le o valor de cada pixel da imagem */
    for (i = 0; i < (*H); i++) {
        for (j = 0; j < (*W); j++) {
            scanf("%d", &img[i][j]);
        }
    }

    return 1;
}

void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i, j;

    /* Escreve os atributos da imagem */
    /* Tipo da imagem: P2 significa pgm*/
    printf("P2\n");
    /* Dimensoes e intensidade maxima da imagem */
    printf("%d %d %d\n", W, H, MaxV);

    /* Escreve os pixels da imagem */
    for (i = 0; i < H; i++) {
        printf("%d", img[i][0]);
        for (j = 1; j < W; j++) {
            printf(" %d", img[i][j]);
        }
        printf("\n");
    }
}

/*----------------FUNCOES A SEREM IMPLEMENTADAS-----------*/
void negativo(int img[][MAX_TAM], int W, int H, int MaxV){
  int i, j;

  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      img[i][j] = MaxV - img[i][j];
    }
  }
}

void rotacao180(int img[][MAX_TAM], int W, int H){
  int i, j, aux;

  for(i = 0; i < (H / 2); i++){
    for(j = 0; j < W; j++){
      aux = img[i][j];
      img[i][j] = img[H - i - 1][W - j - 1];
      img[H - i - 1][W - j - 1] = aux;
    }
  }
}

void detectaBorda(int img[][MAX_TAM], int W, int H, int MaxV){
  int i, j;
  int matriz[H][W];

  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      matriz[i][j] = img[i][j];
    }
  }

  for(i = 1; i < (H - 1); i++){
    for(j = 1; j < (W - 1); j++){
      img[i][j] = (-1*matriz[i-1][j-1]) + (-4*matriz[i-1][j]) + (-1*matriz[i-1][j+1]) + (-4*matriz[i][j-1]) + (20*matriz[i][j]) + (-4*matriz[i][j+1]) + (-1*matriz[i+1][j-1]) + (-4*matriz[i+1][j]) + (-1*matriz[i+1][j+1]);

      if(img[i][j] < 0){
        img[i][j] = 0;
      }

      if(img[i][j] > MaxV){
        img[i][j] = MaxV;
      }
    }
  }
}

void cisalhamento(int img[][MAX_TAM], int W, int H, double Px, double Py){
  int i, j, iLinha, jLinha;
  int matriz[H][W];

  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      matriz[i][j] = img[i][j];
      img[i][j] = 0;
    }
  }

  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      iLinha = i + (Py * j);
      jLinha = j + (Px * i);
      img[iLinha][jLinha] = matriz[i][j];      
    }
  }
}
