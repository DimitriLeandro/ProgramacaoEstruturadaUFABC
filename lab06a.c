#include <stdio.h>

/* VARIAVEIS GLOBAIS */
char mercado[101][101]; /* ARMAZENA A MATRIZ OD MERCADO COM X E ESPACO */
char zumbis[101][4]; /* CADA ZUMBI TEM LATERALIDADE [0], DIRECAO [1], LINHA[2] E COLUNA[3] */
int qtdLinhas, qtdColunas, qtdZumbis;

/* FUNCOES */
void verificarZumbi(int idx, int tempo);
void andarZumbi(int idx, char direcao, int linha, int coluna);
void girarZumbi(int idx, char direcao, char lateralidade);

int main(void){
	int i, j, tempo, totalEmBranco = 0;
	char auxMercado[101];

	/* TEM QUE DEIXAR OS ESPACOS PRO FGETS FUNCIONAR DIREITO */
	scanf(" %d %d ", &qtdLinhas, &qtdColunas);

	/* LENDO A MATRIZ */
	for(i = 0; i < qtdLinhas; i++){
		fgets(auxMercado, (qtdColunas + 3), stdin);
		for(j = 0; j < qtdColunas; j++){
			mercado[i][j] = auxMercado[j];
		}
	}

	/* A PRIMEIRA COISA A FAZER E CADASTRAR OS ZUMBIS */
	scanf("%d", &qtdZumbis);
	for(i = 0; i < qtdZumbis; i++){
		scanf(" %c %c %c %c", &zumbis[i][0], &zumbis[i][1], &zumbis[i][2], &zumbis[i][3]);
	}

	/* AGORA PEGANDO O TEMPO FINAL */
	scanf("%d", &tempo);

	/* PARA CADA ZUMBI, VOU VENDO ONDE ELE ESTA E MUDANDO AS MATRIZES */
	for(i = 0; i < qtdZumbis; i++){
		/* printf("\n\nVERIFICANDO ZUMBI %d:\n", (i + 1)); */
		verificarZumbi(i, tempo);
	}

	/* MOSTRANDO OS ZUMBIS CADASTRADOS */
	for(i = 0; i < qtdZumbis; i++){
		printf("Zumbi %d: (%c, %c, %c)\n", (i + 1), zumbis[i][2], zumbis[i][3], zumbis[i][1]);
	}

	/* EXIBINDO A MATRIZ DO MERCADO */
	printf("\n");
	for(i = 0; i < qtdLinhas; i++){
		for(j = 0; j < qtdColunas; j++){
			printf("%c", mercado[i][j]);
		}
		printf("\n");
	}

	/* POR FIM, VENDO QUANTAS POSICOES NO MERCADO NAO TIVERAM ZUMBIS EM MOMENTO ALGUM */
	for(i = 0; i < qtdLinhas; i++){
		for (j = 0; j < qtdColunas; j++){
			if(mercado[i][j] == ' '){
				totalEmBranco++;
			}
		}
	}

	printf("\n%d\n", totalEmBranco);

	return 0;
}

void verificarZumbi(int idx, int tempo){
	/* LATERALIDADE [0], DIRECAO [1], LINHA[2] E COLUNA[3] */
	int linha = zumbis[idx][2] - '0';
	int coluna = zumbis[idx][3] - '0';
	char direcao = zumbis[idx][1];
	char lateralidade = zumbis[idx][0];

	/* PRIMEIRO DIZENDO QUE UM ZUMBI PASSOU POR AQUI */
	mercado[linha][coluna] = '#';

	/* PREIMEIRO VERIFICANDO SE TEM ALGUMA PRATELEIRA NA FRENTE */
	if((direcao == 'N' && mercado[linha - 1][coluna] == 'X') ||
	   (direcao == 'S' && mercado[linha + 1][coluna] == 'X') ||
	   (direcao == 'E' && mercado[linha][coluna + 1] == 'X') ||
	   (direcao == 'W' && mercado[linha][coluna - 1] == 'X')){
		girarZumbi(idx, direcao, lateralidade);
	}else{
		/* SE CHEGOU AQUI ENTAO PODE IR EM FRENTE */
		andarZumbi(idx, direcao, linha, coluna);
	}

	/* printf("tempo: %d, linha: %c, coluna: %c, direcao: %c)\n", tempo, zumbis[idx][2], zumbis[idx][3], zumbis[idx][1]); */

	if(tempo != 1){
		verificarZumbi(idx, (tempo - 1));
	}else{
		linha = zumbis[idx][2] - '0';
		coluna = zumbis[idx][3] - '0';
		mercado[linha][coluna] = '#';
	}
}

void andarZumbi(int idx, char direcao, int linha, int coluna){
	/* LATERALIDADE [0], DIRECAO [1], LINHA[2] E COLUNA[3] */

	if(direcao == 'N'){
		zumbis[idx][2]--;
	}else if(direcao == 'S'){
		zumbis[idx][2]++;
	}else if(direcao == 'E'){
		zumbis[idx][3]++;
	}else{
		zumbis[idx][3]--;
	}
}

void girarZumbi(int idx, char direcao, char lateralidade){
	/* LATERALIDADE [0], DIRECAO [1], LINHA[2] E COLUNA[3] */
	
	if(direcao == 'N'){
		if(lateralidade == 'R'){
			zumbis[idx][1] = 'E';
		}else{
			zumbis[idx][1] = 'W';
		}
	}else if(direcao == 'S'){
		if(lateralidade == 'R'){
			zumbis[idx][1] = 'W';
		}else{
			zumbis[idx][1] = 'E';
		}
	}else if(direcao == 'E'){
		if(lateralidade == 'R'){
			zumbis[idx][1] = 'S';
		}else{
			zumbis[idx][1] = 'N';
		}
	}else{
		if(lateralidade == 'R'){
			zumbis[idx][1] = 'N';
		}else{
			zumbis[idx][1] = 'S';
		}
	}
}