#include <stdio.h>

/* VARIAVEIS GLOBAIS */
int qtdNumeros, resultadoEsperado, resultadoAtual, total = 0;
int jesusNumeros[6], satanasOperacoes[5], numeros[6], operacoes[5];

/* ASSINATURA DAS FUNCOES */
void lerNumeros();
void permutarNumeros(int limiteInferior, int limiteSuperior);
void trocarNumeros(int i, int j);
void permutarOperacoes();
void fazerConta();
void reorganizarJesusESatanas();


int main(void){
	scanf("%d", &qtdNumeros);
	scanf("%d", &resultadoEsperado);
	
	lerNumeros();

	permutarNumeros(0, (qtdNumeros - 1));

	printf("Existem %d expressoes.\n", total);
	
	return 0;
}

void lerNumeros(){
	int i;

	for(i = 0; i < qtdNumeros; i++){
		scanf("%d", &numeros[i]);
	}
}

void permutarNumeros(int limiteInferior, int limiteSuperior){
	int i;

	if(limiteInferior == limiteSuperior){
		/* AQUI DENTRO O VETOR NUMEROS TEM UMA ORDENACAO ESPECIFICA */
		/* EH HORA DE VERIFICAR AS OPERACOES COM ESSA DETERMINADA CONFIGURACAO */
		permutarOperacoes();
	}else{
		for(i = limiteInferior; i <= limiteSuperior; i++){
			trocarNumeros(limiteInferior, i);
			permutarNumeros((limiteInferior + 1), limiteSuperior);
			trocarNumeros(limiteInferior, i);
		}
	}
}

void trocarNumeros(int i, int j){
	int aux = numeros[i];
	numeros[i] = numeros[j];
	numeros[j] = aux;
}

void permutarOperacoes(){
	int operacoesRealizadas = 0, contA = 0, contB = 0, contC = 0, contD = 0, contE = 0, i, paradaDoWhile = 1;

	/* O WHILE TEM QUE PARAR EM 4 ^ QTDOPERACOES */
	for(i = 1; i <= (qtdNumeros - 1); i++){
		paradaDoWhile *= 4;
	}

	while(operacoesRealizadas < paradaDoWhile){
		operacoes[0] = contE;
		operacoes[1] = contD;
		operacoes[2] = contC;
		operacoes[3] = contB;
		operacoes[4] = contA;

		/* OS VETORES JESUSNUMEROS E SATANASOPERACOES GUARDAM QUAIS NUMEROS E OPERACOES AINDA FALTAM PRA SEREM FEITAS */
		/* COMO VAMOS FAZER TODAS AS OPERACOES COM O NUMERO QUE ACABOU DE CHEGAR, TENHO QUE COPIAR OS VETORES */
		for(i = 0; i < qtdNumeros; i++){
			jesusNumeros[i] = numeros[i];
			if(i != (qtdNumeros - 1)){
				satanasOperacoes[i] = operacoes[i];
			}
		}	
		
		fazerConta(qtdNumeros);
		
		if(resultadoAtual == resultadoEsperado){
			total++;
		}

		contE++;
		if(contE == 4){
			contE = 0;
			contD++;
			if(contD == 4){
				contD = 0;
				contC++;
				if(contC == 4){
					contC = 0;
					contB++;
					if(contB == 4){
						contB = 0;
						contA++;
					}
				}
			}
		}
		
		operacoesRealizadas ++;
	}
}

void fazerConta(int quantosNumerosFaltam){
	/* O VETOR OPERACOES JA ESTA COM AS CONTAS NA ORDEM CERTA E OS NUMEROS TAMBEM ESTAO ORDENADOS */
	/* FALTA ORGANIZAR A CONTA QUE VAI SER FEITA */

	/* PRIMEIRO EU BRECO A DIVISAO POR 0 */
	if(satanasOperacoes[0] == 3 && jesusNumeros[1] == 0){
		resultadoAtual = resultadoEsperado + 1;
	}else{
		if(quantosNumerosFaltam == 2){
			/* SE SO FALTAM DOIS NUMEROS, ENTAO E A ULTIMA OPERACAO */
			switch(satanasOperacoes[0]){
				case 0: 
					resultadoAtual = jesusNumeros[0] + jesusNumeros[1];
					break;
				case 1: 
					resultadoAtual = jesusNumeros[0] - jesusNumeros[1];
					break;
				case 2: 
					resultadoAtual = jesusNumeros[0] * jesusNumeros[1];
					break;
				case 3: 
					resultadoAtual = jesusNumeros[0] / jesusNumeros[1];
					break;
			}
		}else{
			/* SE FALTAR MAIS DE UMA OPERACAO PRA FAZER, ENTAO VAI COLOCANDO O RESULTADO EM JESUSNUMEROS[0] */
			/* E A PROXIMA OPERACAO VAI ENTRE JESUSNUMEROS[0] E JESUSNUMEROS[1] */
			quantosNumerosFaltam--;
			switch(satanasOperacoes[0]){
				case 0:
					jesusNumeros[0] = jesusNumeros[0] + jesusNumeros[1];
					reorganizarJesusESatanas();
					fazerConta(quantosNumerosFaltam);
					break;
				case 1: 
					jesusNumeros[0] = jesusNumeros[0] - jesusNumeros[1];
					reorganizarJesusESatanas();
					fazerConta(quantosNumerosFaltam);
					break;
				case 2: 
					jesusNumeros[0] = jesusNumeros[0] * jesusNumeros[1];
					reorganizarJesusESatanas();
					fazerConta(quantosNumerosFaltam);
					break;
				case 3: 
					jesusNumeros[0] = jesusNumeros[0] / jesusNumeros[1];
					reorganizarJesusESatanas();
					fazerConta(quantosNumerosFaltam);
					break;
			}
		}	
	}		
}

void reorganizarJesusESatanas(){
	jesusNumeros[1] = jesusNumeros[2];
	jesusNumeros[2] = jesusNumeros[3];
	jesusNumeros[3] = jesusNumeros[4];
	jesusNumeros[4] = jesusNumeros[5];
	satanasOperacoes[0] = satanasOperacoes[1];
	satanasOperacoes[1] = satanasOperacoes[2];
	satanasOperacoes[2] = satanasOperacoes[3];
	satanasOperacoes[3] = satanasOperacoes[4];
}