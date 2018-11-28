#include <stdio.h>
#include <string.h>

/* DEFININDO AS NOVAS ESTRUTURAS */
typedef struct {
	char nome[30];
	int pontos;
	int golsMarcados;	
	int golsSofridos;
} Time;

typedef struct{
	Time vetorEquipes[4];
	int qtdTimes;
} Grupo;


/* ASSINATURA DAS FUNÇÕES */
void atualizarTabelaDoGrupo(Grupo *grupo, char *nome, int golsMarcados, int golsSofridos);
void ordenarGrupo(Grupo *grupo);
void trocarTimesDePosicao(Grupo *grupo, int a, int b);
int verificarMelhorColocado(Time t1, Time t2);

int main(){
	/* DECLARAÇÃO DE VARIÁVEIS */
	int numJogos, contadorGrupo, contadorJogos, contadorEquipe, golsA, golsB, i, indicadorProximoOuAnterior;
	char nomeA[30], nomeB[30];
	Grupo vetorGrupos[8];

	/* VARIAVEIS AUXILIARES QUE SÓ VÃO SERVIR PRA SEREM PRINTADAS */
	char nomeX[30];
	int pontosX, golsMarcadosX, golsSofridosX, saldoGolsX;

	/* LEITURA DOS DADOS DE ENTRADA */
	for (contadorGrupo = 0; contadorGrupo < 8; contadorGrupo++){
		/* O GRUPO COMEÇA COM 0 TIMES */
		vetorGrupos[contadorGrupo].qtdTimes = 0;

		/* CADA GRUPO TEM 6 JOGOS */
		for(contadorJogos = 0; contadorJogos < 6; contadorJogos++){
			scanf("%s %d x %d %s", nomeA, &golsA, &golsB, nomeB);
			atualizarTabelaDoGrupo(&vetorGrupos[contadorGrupo], nomeA, golsA, golsB);
			atualizarTabelaDoGrupo(&vetorGrupos[contadorGrupo], nomeB, golsB, golsA);
		}
	}

	/* ORDENANDO OS GRUPOS */
	for(contadorGrupo = 0; contadorGrupo < 8; contadorGrupo++){
		ordenarGrupo(&vetorGrupos[contadorGrupo]);
	}

	/* PRINTANDO O ESTADO FINAL DE CADA GRUPO */
	for (contadorGrupo = 0; contadorGrupo < 8; contadorGrupo++){
		printf("Grupo %c:\n", (contadorGrupo + 65)); /* A B C... */
		for(contadorEquipe = 0; contadorEquipe < 4; contadorEquipe++){
			
			strcpy(nomeX, vetorGrupos[contadorGrupo].vetorEquipes[contadorEquipe].nome);
			pontosX = vetorGrupos[contadorGrupo].vetorEquipes[contadorEquipe].pontos;
			golsMarcadosX = vetorGrupos[contadorGrupo].vetorEquipes[contadorEquipe].golsMarcados;
			golsSofridosX = vetorGrupos[contadorGrupo].vetorEquipes[contadorEquipe].golsSofridos;
			saldoGolsX = golsMarcadosX - golsSofridosX;

			printf("%-15s %3d %3d %3d %3d\n", nomeX, pontosX, golsMarcadosX, golsSofridosX, saldoGolsX);
		}
		printf("\n");
	}

	/*  PRINTANDO AS OITAVAS DE FINAL:
		1o colocado do Grupo A x 2o colocado do Grupo B
		1o colocado do Grupo B x 2o colocado do Grupo A
		1o colocado do Grupo C x 2o colocado do Grupo D
		1o colocado do Grupo D x 2o colocado do Grupo C
		1o colocado do Grupo E x 2o colocado do Grupo F
		1o colocado do Grupo F x 2o colocado do Grupo E
		1o colocado do Grupo G x 2o colocado do Grupo H
		1o colocado do Grupo H x 2o colocado do Grupo G
	*/

	printf("Oitavas de final:\n");

	indicadorProximoOuAnterior = 1; /* 1 -> PRÓXIMO, 0 -> ANTERIOR*/
	for(i = 0; i < 8; i++){
		if(indicadorProximoOuAnterior == 1){
			printf("%15s x %s\n", vetorGrupos[i].vetorEquipes[0].nome, vetorGrupos[i + 1].vetorEquipes[1].nome);
			indicadorProximoOuAnterior = 0;
		}else{
			printf("%15s x %s\n", vetorGrupos[i].vetorEquipes[0].nome, vetorGrupos[i - 1].vetorEquipes[1].nome);
			indicadorProximoOuAnterior = 1;
		}
	}

	return 0;
}

/* Atualiza os atributos de um time na tabela de classificacao */
void atualizarTabelaDoGrupo(Grupo *grupo, char *nome, int golsMarcados, int golsSofridos) {
	int i;
	int idTime = (*grupo).qtdTimes; /* ja começa na posiçaõ em que um time novo é cadastrado */

	/* PRIMEIRO VERIFICANDO SE ESSE TIME JÁ ESTÁ CADASTRADO */
	for(i = 0; i < (*grupo).qtdTimes; i++){
		/* SE O NOME É IGUAL... */
		if(strcmp((*grupo).vetorEquipes[i].nome, nome) == 0){
			/* ...ENTÃO O TIME JÁ ESTA CADASTRADO */
			idTime = i;
			break;
		}
	}

	/* SE O idTime FOR *num_times ENTÃO CRIO UM CADASTRO NOVO E SOMO +1 EM num_times */
	if(idTime == (*grupo).qtdTimes){
		/* primeiros atributos zerados */
		strcpy((*grupo).vetorEquipes[idTime].nome, nome);
		(*grupo).vetorEquipes[idTime].pontos = 0;
		(*grupo).vetorEquipes[idTime].golsMarcados = 0;
		(*grupo).vetorEquipes[idTime].golsSofridos = 0;
		
		/* +1 TIME NESSE GRUPO */
		(*grupo).qtdTimes = (*grupo).qtdTimes + 1;
	}

	/* ATUALIZANDO */
	(*grupo).vetorEquipes[idTime].golsMarcados = (*grupo).vetorEquipes[idTime].golsMarcados + golsMarcados;
	(*grupo).vetorEquipes[idTime].golsSofridos = (*grupo).vetorEquipes[idTime].golsSofridos + golsSofridos;

	/* atributos que dependem se o time ganhou ou perdeu */
	/* SE EMPATOU */
	if(golsMarcados == golsSofridos){
		(*grupo).vetorEquipes[idTime].pontos = (*grupo).vetorEquipes[idTime].pontos + 1;
	}else{
		/* SE GANHOU */
		if(golsMarcados > golsSofridos){
			(*grupo).vetorEquipes[idTime].pontos = (*grupo).vetorEquipes[idTime].pontos + 3;
		}
	}
}

/* Ordena a tabela de times por selection sort */
void ordenarGrupo(Grupo *grupo) {
	int i, j, idMelhorTime;

	for(i = 0; i < 3; i++){
		idMelhorTime = i;
		for(j = (i + 1); j < 4; j++){
			if(verificarMelhorColocado((*grupo).vetorEquipes[j], (*grupo).vetorEquipes[idMelhorTime])){
				idMelhorTime = j;
			}
		}
		if(idMelhorTime != i){
			trocarTimesDePosicao(grupo, idMelhorTime, i);
		}
	}
}

void trocarTimesDePosicao(Grupo *grupo, int a, int b){
	Time aux;

	/* AUX = A */
	strcpy(aux.nome, (*grupo).vetorEquipes[a].nome);
	aux.pontos = (*grupo).vetorEquipes[a].pontos;
	aux.golsMarcados = (*grupo).vetorEquipes[a].golsMarcados; 
	aux.golsSofridos = (*grupo).vetorEquipes[a].golsSofridos;

	/* A = B */
	strcpy((*grupo).vetorEquipes[a].nome, (*grupo).vetorEquipes[b].nome);
	(*grupo).vetorEquipes[a].pontos = (*grupo).vetorEquipes[b].pontos;
	(*grupo).vetorEquipes[a].golsMarcados = (*grupo).vetorEquipes[b].golsMarcados; 
	(*grupo).vetorEquipes[a].golsSofridos = (*grupo).vetorEquipes[b].golsSofridos;

	/* B = AUX */
	strcpy((*grupo).vetorEquipes[b].nome, aux.nome);
	(*grupo).vetorEquipes[b].pontos = aux.pontos;
	(*grupo).vetorEquipes[b].golsMarcados = aux.golsMarcados; 
	(*grupo).vetorEquipes[b].golsSofridos = aux.golsSofridos;
}

int verificarMelhorColocado(Time t1, Time t2) {
	/*
		Maior número de pontos
		Maior saldo de gols (diferença entre gols feitos e sofridos).
		Maior número de gols marcados.
		Menor nome (considerando a ordem lexicográfica).
	*/

	/* PONTOS */
	if(t1.pontos > t2.pontos){
		return 1;
	}
	else if(t2.pontos > t1.pontos){
		return 0;
	}
	/* CASO DE EMPATE */
	else{
		/* SALDO DE GOLS */
		if((t1.golsMarcados - t1.golsSofridos) > (t2.golsMarcados - t2.golsSofridos)){
			return 1;
		}
		else if((t2.golsMarcados - t2.golsSofridos) > (t1.golsMarcados - t1.golsSofridos)){
			return 0;
		}
		/* CASO DE EMPATE */
		else{
			/* GOLS MARCADOS */
			if(t1.golsMarcados > t2.golsMarcados){
				return 1;
			}
			else if(t2.golsMarcados > t1.golsMarcados){
				return 0;
			}
			/* CASO DE EMPATE */
			else{
				/* MENOR NOME NA ORDEM ALFABETICA */
				if(strcmp(t1.nome, t2.nome) < 0){
					return 1;
				}else{
					return 0;
				}
			}
		}
	}
}