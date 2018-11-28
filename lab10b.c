#include <stdio.h>
#include <string.h>

/* Tamanho maximo de um nome de time */
#define MAX_NOME 26
/* Numero maximo de partidas */
#define MAX_TIMES 400

struct Time {
	char nome[MAX_NOME];
	int pontos;
	int gols_feitos;
	int saldo_gols;
	int num_vitorias;
};
typedef struct Time Time;

/* Atualiza os atributos de um time na tabela de classificacao */
void atualiza_tabela(Time tabela[], int *num_times, char *nome, int gols_feitos, int gols_sofridos) {
	int i;
	int idTime = *num_times; /* ja começa na posiçaõ em que um time novo é cadastrado */

	/* PRIMEIRO VERIFICANDO SE ESSE TIME JÁ ESTÁ CADASTRADO */
	for(i = 0; i < *num_times; i++){
		/* SE O NOME É IGUAL... */
		if(strcmp(tabela[i].nome, nome) == 0){
			/* ...ENTÃO O TIME JÁ ESTA CADASTRADO */
			idTime = i;
			break;
		}
	}

	/* SE O idTime FOR *num_times ENTÃO CRIO UM CADASTRO NOVO E SOMO +1 EM num_times */
	if(idTime == *num_times){
		/* primeiros atributos zerados */
		strcpy(tabela[idTime].nome, nome);
		tabela[idTime].pontos = 0;
		tabela[idTime].gols_feitos = 0;
		tabela[idTime].saldo_gols = 0;
		tabela[idTime].num_vitorias = 0;
		
		/* +1 TIME NA LISTA */
		*num_times = *num_times + 1;
	}

	/* ATUALIZANDO */
	tabela[idTime].gols_feitos = tabela[idTime].gols_feitos + gols_feitos;
	tabela[idTime].saldo_gols = tabela[idTime].saldo_gols + gols_feitos - gols_sofridos;

	/* atributos que dependem se o time ganhou ou perdeu */
	/* SE EMPATOU */
	if(gols_feitos == gols_sofridos){
		tabela[idTime].pontos = tabela[idTime].pontos + 1;
	}else{
		/* SE GANHOU */
		if(gols_feitos > gols_sofridos){
			tabela[idTime].pontos = tabela[idTime].pontos + 3;        
			tabela[idTime].num_vitorias = tabela[idTime].num_vitorias + 1;
		}
	}
}

/* Determina qual dos dois times eh o mais bem classificado.
 * Retorna 1 se t1 é o melhor e 0 caso contrário */
int eh_maior(Time t1, Time t2) {
	/*
		Maior número de pontos
		Maior número de vitórias.
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
		/* VITÓRIAS */
		if(t1.num_vitorias > t2.num_vitorias){
			return 1;
		}
		else if(t2.num_vitorias > t1.num_vitorias){
			return 0;
		}
		/* CASO DE EMPATE */
		else{
			/* SALDO DE GOLS */
			if(t1.saldo_gols > t2.saldo_gols){
				return 1;
			}
			else if(t2.saldo_gols > t1.saldo_gols){
				return 0;
			}
			/* CASO DE EMPATE */
			else{
				/* GOLS MARCADOS */
				if(t1.gols_feitos > t2.gols_feitos){
					return 1;
				}
				else if(t2.gols_feitos > t1.gols_feitos){
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
}

void trocarTimesDePosicao(Time tabela[], int a, int b){
	Time aux;

	/*  aux = a
		a = b
		b = aux
	*/

	/* AUX = A */
	strcpy(aux.nome, tabela[a].nome);
	aux.pontos = tabela[a].pontos;
	aux.gols_feitos = tabela[a].gols_feitos; 
	aux.saldo_gols = tabela[a].saldo_gols;
	aux.num_vitorias = tabela[a].num_vitorias;

	/* A = B */
	strcpy(tabela[a].nome, tabela[b].nome);
	tabela[a].pontos = tabela[b].pontos;
	tabela[a].gols_feitos = tabela[b].gols_feitos; 
	tabela[a].saldo_gols = tabela[b].saldo_gols;
	tabela[a].num_vitorias = tabela[b].num_vitorias;

	/* B = AUX */
	strcpy(tabela[b].nome, aux.nome);
	tabela[b].pontos = aux.pontos;
	tabela[b].gols_feitos = aux.gols_feitos; 
	tabela[b].saldo_gols = aux.saldo_gols;
	tabela[b].num_vitorias = aux.num_vitorias;
}

/* Ordena a tabela de times por selection sort */
void ordena_times(Time tabela[], int n) {
	int i, j, idMelhorTime;

	for(i = 0; i < (n - 1); i++){
		idMelhorTime = i;
		for(j = (i + 1); j < n; j++){
			if(eh_maior(tabela[j], tabela[idMelhorTime])){
				idMelhorTime = j;
			}
		}
		if(idMelhorTime != i){
			trocarTimesDePosicao(tabela, idMelhorTime, i);
		}
	}
}

int main(){
	int num_jogos, num_times, i;
	int gols1, gols2;
	char nome_time1[MAX_NOME], nome_time2[MAX_NOME];
	Time tabela[MAX_TIMES];

	/* Lendo a entrada */
	scanf("%d", &num_jogos);
	for (i = 0; i < num_jogos; i++) {
		scanf("%s %d x %d %s", nome_time1, &gols1, &gols2, nome_time2);
		atualiza_tabela(tabela, &num_times, nome_time1, gols1, gols2);
		atualiza_tabela(tabela, &num_times, nome_time2, gols2, gols1);
	}

	/* Ordenando a tabela de times */
	ordena_times(tabela, num_times);

	/* Escrevendo a saida */
	for (i = 0; i < num_times; i++) {
		printf("%-30s %5d %5d %5d %5d\n", tabela[i].nome, tabela[i].pontos, tabela[i].num_vitorias, tabela[i].saldo_gols, tabela[i].gols_feitos);
	}

	return 0;
}
