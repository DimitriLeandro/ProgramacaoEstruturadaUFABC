#include <stdio.h>
#include <stdlib.h>

/* DEFININDO A ESTRUTURA CARTA */
struct Carta
{
	char nome[30];
	int caracteristicas[8];
};

typedef struct Carta Carta;

/* DECLARANDO FUNCOES */
void lerCaracteristicasEscolhidas(int *ponteiroQtdRodadas, int *caracteristicaCadaRodada);
FILE * abrirArquivoEntrada(char *argumento1);
void lerQtdCartasEJogadorDaVez(FILE *fileIn, int *qtdCartasJogador1, int *qtdCartasJogador2, int *jogadorDaVez);
void lerBaralho(FILE *fileIn, Carta *ponteiroBaralho, int qtdCartas);
void exibirBaralho(Carta *ponteiroBaralho, int qtdCartas);
void jogarRodada(int contRodada, int *jogadorDaVez, int caracteristicaEscolhida, Carta *ponteiroBaralhoJogador1, int *qtdCartasJogador1, Carta *ponteiroBaralhoJogador2, int *qtdCartasJogador2);
void adicionarCartaAoFinal(Carta *baralho, int *qtdCartasJogador, Carta carta);
void escreverEstadoAtual(char nomeArquivo[10], int qtdCartasJogador1, int qtdCartasJogador2, int jogadorDaVez, Carta *baralhoJogador1, Carta *baralhoJogador2);

/*  VARIAVEIS GLOBAIS 
	essas aqui so vao ser usadas na hora de escrever o resultado final 
	pq o tamanho do vetor baralho e uma coisa, a qtd real de cartas que cada um tem e outra	
*/
int qtdRealCartasJ1;
int qtdRealCartasJ2;

int main(int qtdArgumentos, char **argumentos){
	int qtdRodadas, i, qtdCartasJogador1, qtdCartasJogador2, jogadorDaVez, *caracteristicaCadaRodada;
	FILE *fileIn;
	Carta *baralhoJogador1, *baralhoJogador2;

	/* PRIMEIRO PEGO O NÚMERO DE RODADAS... */
	scanf(" %d ", &qtdRodadas);
	/* printf("Quantidade de rodadas: %d\n\n", qtdRodadas); */

	/* ...E LEIO QUAL FOI A CARACTERISTICA ESCOLHIDA EM CADA UMA */
	/* ALOCANDO MEMORIA PARA O VETOR caracteristicasCadaRodada E LENDO ESSE VETOR */
	caracteristicaCadaRodada = malloc(qtdRodadas * sizeof(int));
	lerCaracteristicasEscolhidas(&qtdRodadas, caracteristicaCadaRodada);

	/* ABRINDO O ARQUIVO DE ENTRADA ./lab09c arqXX.in1 arqXX.res < arqXX.in2 */
	fileIn = abrirArquivoEntrada(argumentos[1]);

	/* FUNÇÃO QUE VAI LER QUANTAS CARTAS CADA UM TEM E DE QUEM E A VEZ */
	lerQtdCartasEJogadorDaVez(fileIn, &qtdCartasJogador1, &qtdCartasJogador2, &jogadorDaVez);
	
	/* printf("Jogador 1: %d cartas\n", qtdCartasJogador1);
	printf("Jogador 2: %d cartas\n", qtdCartasJogador2);
	printf("Jogador da vez: %d\n\n", jogadorDaVez); */

	/* SETANDO A QTD REAL DE CARTAS QUE CADA UM TEM */
	qtdRealCartasJ1 = qtdCartasJogador1;
	qtdRealCartasJ2 = qtdCartasJogador2;

	/* CRIANDO O BARALHO DE CADA JOGADOR E ALOCANDO MEMORIA*/
	/*  O NUMERO MAXIMO DE CARTAS QUE PODE SER CONSEGUIDO POR UM JOGADOR EH 
		2 * qtdRodadas (supondo que ele ganhe tudo).
		PORTANTO, TENHO QUE ALOCAR O QUE ELE JA TEM E + ISSO
	*/
	baralhoJogador1 = malloc(((2 * qtdRodadas) + qtdCartasJogador1) * sizeof(Carta));
	baralhoJogador2 = malloc(((2 * qtdRodadas) + qtdCartasJogador2) * sizeof(Carta));

	/* LENDO OS BARALHOS */
	lerBaralho(fileIn, baralhoJogador1, qtdCartasJogador1);
	lerBaralho(fileIn, baralhoJogador2, qtdCartasJogador2);

	/*  FAZENDO UMA RODADA DE CADA VEZ 
		CADA RODADA TEM O JOGADOR DA VEZ E A CARACTERISTICA ESCOLHIDA */
	/* printf("\nCOMEÇANDO O JOGO\n\n"); */
	for(i = 0; i < qtdRodadas; i++){
		jogarRodada(i, &jogadorDaVez, caracteristicaCadaRodada[i], baralhoJogador1, &qtdCartasJogador1, baralhoJogador2, &qtdCartasJogador2);
	}

	/* EXIBINDO OS BARALHOS 
	exibirBaralho(baralhoJogador1, qtdCartasJogador1);
	exibirBaralho(baralhoJogador2, qtdCartasJogador2); */

	/* FINALMENTE ESCREVENDO O ESTADO ATUAL NO ARQUIVO arqxx (sem extensao) */
	escreverEstadoAtual(argumentos[2], qtdCartasJogador1, qtdCartasJogador2, jogadorDaVez, baralhoJogador1, baralhoJogador2);

	return 0;
}

void escreverEstadoAtual(char nomeArquivo[10], int qtdCartasJogador1, int qtdCartasJogador2, int jogadorDaVez, Carta *baralhoJogador1, Carta *baralhoJogador2){
	/* CRIANDO O NOME DO ARQUIVO SEM EXTENSAO */
	char nomeFileOut[10];
	int p = 0, f = 0;
	FILE *fileOut;

	do{
		nomeFileOut[p] = nomeArquivo[p];
		p++;
	}while(nomeArquivo[p] != '.');

	/* ABRINDO O ARQUIVO NO MODO APPEND -> a */
	fileOut = fopen(nomeFileOut, "a");

	/* PRIMEIRA LINHA */
	fprintf(fileOut, "%d %d %d\n", qtdRealCartasJ1, qtdRealCartasJ2, jogadorDaVez);

	/* BARALHO 1 */
	for(p = (qtdCartasJogador1 - qtdRealCartasJ1); p < qtdCartasJogador1; p++){
		fprintf(fileOut, "%s\n", baralhoJogador1[p].nome);
		for(f = 0; f < 8; f++){
			fprintf(fileOut, "%d ", baralhoJogador1[p].caracteristicas[f]);
		}
		fprintf(fileOut, "\n");
	}

	/* BARALHO 2 */
	for(p = (qtdCartasJogador2 - qtdRealCartasJ2); p < qtdCartasJogador2; p++){
		fprintf(fileOut, "%s\n", baralhoJogador2[p].nome);
		for(f = 0; f < 8; f++){
			fprintf(fileOut, "%d ", baralhoJogador2[p].caracteristicas[f]);
		}
		fprintf(fileOut, "\n");
	}
}

/* FUNÇÃO QUE FAZ UMA RODADA DO JOGO */
void jogarRodada(int contRodada, int *jogadorDaVez, int caracteristicaEscolhida, Carta *ponteiroBaralhoJogador1, int *qtdCartasJogador1, Carta *ponteiroBaralhoJogador2, int *qtdCartasJogador2){
	/* CONFORME O JOGO FOR ROLANDO, AS CARTAS VAO SENDO COLOCADAS NO FINAL DE CADA */

	int vencedorRodada;

	/* LEMBRANDO QUE AS CARACTERISTICAS VAO DE 0 A 7 E NAO DE 1 A 8 */
	caracteristicaEscolhida--;

	/* printf("\nRODADA %d\n", (contRodada + 1));
	if(*jogadorDaVez == 1){
		printf("Jogador da Vez: %d (%d cartas no vetor e %d cartas reais)\n", *jogadorDaVez, *qtdCartasJogador1, qtdRealCartasJ1);
	}else{
		printf("Jogador da Vez: %d (%d cartas no vetor e %d cartas reais)\n", *jogadorDaVez, *qtdCartasJogador2, qtdRealCartasJ2);
	}
	printf("Caracteristica Escolhida: %d\n", caracteristicaEscolhida);
	printf("Comparando baralhos na posição %d\n", contRodada);
	printf("%s vs. %s\n", ponteiroBaralhoJogador1[contRodada].nome, ponteiroBaralhoJogador2[contRodada].nome);
	printf("%d vs. %d\n", ponteiroBaralhoJogador1[contRodada].caracteristicas[caracteristicaEscolhida], ponteiroBaralhoJogador2[contRodada].caracteristicas[caracteristicaEscolhida]); */

	/* SE DEU EMPATE */
	if(ponteiroBaralhoJogador1[contRodada].caracteristicas[caracteristicaEscolhida] == ponteiroBaralhoJogador2[contRodada].caracteristicas[caracteristicaEscolhida]){
		/*printf("Empate\n"); */
		vencedorRodada = *jogadorDaVez;
	}else{
		/* SE NAO DEU EMPATE ENTAO EU VEJO QUEM TEM A CARACTERISTICA COM MAIOR VALOR */
		/* JOGADOR 1 COM O MAIOR VALOR */
		if(ponteiroBaralhoJogador1[contRodada].caracteristicas[caracteristicaEscolhida] > ponteiroBaralhoJogador2[contRodada].caracteristicas[caracteristicaEscolhida]){
			vencedorRodada = 1;
		}
		/* JOGADOR COM O MAIOR VALOR */
		else{
			vencedorRodada = 2;
		}

		/* MAS TENHO QUE LEMBRAR QUE NEM TODA CARACTERISTICA GANHA COM O MAIOR VALOR */
		/* AS CARACTERISTICAS 2, 5, 6 E 7 GANHAM COM O MENOR VALOR */
		/* AS CARACTERISTICAS 0, 1, 3 E 4 GANHAM COM O MAIOR VALOR */
		if(caracteristicaEscolhida == 2 || caracteristicaEscolhida == 5 || caracteristicaEscolhida == 6 || caracteristicaEscolhida == 7){
			/* SE ENTROU AQUI ENTAO A CARACTERISTICA ESCOLHIDA E DE MENOR VALOR, TENHO QUE TROCAR O VENCEDOR */
			if(vencedorRodada == 1){
				vencedorRodada = 2;
			}else{
				vencedorRodada = 1;
			}
		}
	}		

	/* ARRUMANDO AS COISAS PRO VENCEDOR */
	if(vencedorRodada == 1){
		adicionarCartaAoFinal(ponteiroBaralhoJogador1, qtdCartasJogador1, ponteiroBaralhoJogador1[contRodada]);
		adicionarCartaAoFinal(ponteiroBaralhoJogador1, qtdCartasJogador1, ponteiroBaralhoJogador2[contRodada]);
		qtdRealCartasJ1 += 1;
		qtdRealCartasJ2 -= 1;
		*jogadorDaVez = 1;
		/* printf("O jogador 1 ganhou\n"); */
	}else{
		adicionarCartaAoFinal(ponteiroBaralhoJogador2, qtdCartasJogador2, ponteiroBaralhoJogador2[contRodada]);
		adicionarCartaAoFinal(ponteiroBaralhoJogador2, qtdCartasJogador2, ponteiroBaralhoJogador1[contRodada]);
		qtdRealCartasJ1 -= 1;
		qtdRealCartasJ2 += 1;
		*jogadorDaVez = 2;
		/* printf("O jogador 2 ganhou\n"); */
	}
	/* printf("Jogador 1: %d cartas no vetor e %d cartas reais\n", *qtdCartasJogador1, qtdRealCartasJ1);
	printf("Jogador 2: %d cartas no vetor e %d cartas reais\n", *qtdCartasJogador2, qtdRealCartasJ2); */
}

void adicionarCartaAoFinal(Carta *baralho, int *qtdCartasJogador, Carta carta){
	/*  
		VOU ADICIONAR A CARTA ponteiroCarta NO BARALHO baralho NA POSICAO qtdCartasJogador 
		E SOMAR MAIS UMA CARTA PRA ESSE JOGADOR 
	*/

	int k = 0;

	/* printf("Adicionando a carta %s ao baralho na posicao %d.\n", carta.nome, *qtdCartasJogador); */

	/* NOME DA CARTA */
	do{
		baralho[*qtdCartasJogador].nome[k] = carta.nome[k];
		k++;
	}while(carta.nome[k - 1] != '\0');

	/* CARACTERISTICAS */
	for(k = 0; k < 8; k++){
		baralho[*qtdCartasJogador].caracteristicas[k] = carta.caracteristicas[k];
	}

	*qtdCartasJogador = *qtdCartasJogador + 1;

	/* printf("Agora esse jogador tem %d cartas no vetor.\n", *qtdCartasJogador);*/
}

/* FUNCAO QUE ARMAZENA A CARACTERISTICA ESCOLHIDA EM CADA RODADA E ARMAZENA EM caracteristicaCadaRodada */
void lerCaracteristicasEscolhidas(int *ponteiroQtdRodadas, int *caracteristicaCadaRodada){
	int i;
	
	for(i = 0; i < *ponteiroQtdRodadas; i++){
		scanf(" %d ", &caracteristicaCadaRodada[i]);
		/* printf("Caracteristica escolhida na rodada %d: %d\n", (i + 1), caracteristicaCadaRodada[i]); */
	}
	/* printf("\n"); */
}

/* FUNCAO TESTE PARA EXIBIR O BARALHO */
void exibirBaralho(Carta *ponteiroBaralho, int qtdCartas){
	int i, j;

	printf("\nEXIBINDO BARALHO...\n");

	for(i = 0; i < qtdCartas; i++){
		printf("%s\n", ponteiroBaralho[i].nome);
		for(j = 0; j < 8; j++){
			printf("%d ", ponteiroBaralho[i].caracteristicas[j]);
		}
		printf("\n");
	}

	printf("\n");
}

/* FUNCAO QUE ABRE O ARQUIVO DE ENTRADA E RETORNA O PONTEIRO FILE */
FILE * abrirArquivoEntrada(char *argumento1){
	/*  ABRINDO O ARQUIVO IN NO MODO DE LEITURA "r" -> read */
	FILE *fileIn;
	fileIn = fopen(argumento1, "r");

	if(fileIn == NULL){
		printf("Falha ao abrir o arquivo de entrada. \n");
		return NULL;
	}

	return fileIn;
}

/* FUNÇÃO QUE VAI LER QUANTAS CARTAS CADA UM TEM E DE QUEM E A VEZ */
void lerQtdCartasEJogadorDaVez(FILE *fileIn, int *qtdCartasJogador1, int *qtdCartasJogador2, int *jogadorDaVez){
	fscanf(fileIn, " %d ", qtdCartasJogador1);
	fscanf(fileIn, " %d ", qtdCartasJogador2);
	fscanf(fileIn, " %d ", jogadorDaVez);
}

/* FUNÇÃO QUE LE UM BARALHO COMPLETO */
void lerBaralho(FILE *fileIn, Carta *ponteiroBaralho, int qtdCartas){
	int i, j, k, l;
	char letra, valorCaracteristica[30];

	/* printf("COMEÇANDO A LER UM BARALHO\n"); */

	/* PARA CADA CARTA... */
	for(i = 0; i < qtdCartas; i++){
		/* printf("\nLendo a carta %d:\n", (i + 1)); */

		/* LENDO O NOME */
		j = 0;
		do{
			letra = fgetc(fileIn);
			if(letra != '\n' && letra != '\0'){
				ponteiroBaralho[i].nome[j] = letra;
			}
			j++;
		}while(letra != '\n' && letra != '\0');
		ponteiroBaralho[i].nome[j] = '\0';
		/* printf("%s\n", ponteiroBaralho[i].nome); */

		/* LENDO CARACTERISTICAS */
		for(j = 0; j < 8; j++){
			fscanf(fileIn, " %d ", &ponteiroBaralho[i].caracteristicas[j]);
			/* printf("%d ", ponteiroBaralho[i].caracteristicas[j]); */
		}
		/* printf("\n"); */
	}	
}