/*
	DIMITRI LEANDRO DE OLIVEIRA SILVA
	11201720576
*/
#include <stdio.h>

int main(int qtdArgumentos, char **argumentos){

	int i, fimMegaComentario = 1;
	char nomearqin[21], nomearqout[21], ultimoCaracter;
	FILE *fileIn;
	FILE *fileOut;
 
 	/* LENDO O PRIMEIRO ARGUMENTO nomearqin */
 	i = 0;
   	while(argumentos[1][i] != '\0'){
   		nomearqin[i] = argumentos[1][i];
   		i++;
   	}

   	/* LENDO O SEGUNDO ARGUMENTO nomearqout */
   	/* VAI SER UM ARQUIVO .res NAO .out, ENTAO PARO DE LER NO '.'*/
   	i = 0;
   	while(argumentos[2][i] != '.'){
   		nomearqout[i] = argumentos[2][i];
   		i++;
   	}

 
 	/* ABRINDO O ARQUIVO IN NO MODO DE LEITURA "r" -> read */
	fileIn = fopen(nomearqin, "r");

	/* ABRINDO O ARQUIVO OUT NO MODO 'a' -> append */
	fileOut = fopen(nomearqout, "a");
	
	/* CONSIDERANDO QUE O ARQUIVO IN SEMPRE VAI EXISTIR */
	/* LEIO CHAR POR CHAR */
	ultimoCaracter = fgetc(fileIn);
	while(ultimoCaracter != EOF){
		if(ultimoCaracter == '/'){
			/* VAI COMEÇAR UM COMENTARIO, DEVO IDENTIFICAR DE QUAL TIPO */
			ultimoCaracter = fgetc(fileIn);
			if(ultimoCaracter != EOF){
				/* COMENTARIO SIMPLES */
				if(ultimoCaracter == '/'){
					ultimoCaracter = fgetc(fileIn);
					while(ultimoCaracter != '\n'){
						ultimoCaracter = fgetc(fileIn);
					}
					/* ESCREVENDO NO ARQUIVO OUT */
					fprintf(fileOut, "\n");
				}
				/* MEGA COMENTARIO */
				else if(ultimoCaracter == '*'){
					fimMegaComentario = 0;
					while(fimMegaComentario == 0){
						ultimoCaracter = fgetc(fileIn);
						while(ultimoCaracter != '*'){
							ultimoCaracter = fgetc(fileIn);
						}
						ultimoCaracter = fgetc(fileIn);
						if(ultimoCaracter == '/'){
							fimMegaComentario = 1;
						}
					}
				}
				/* NADA */
				else{
					/* ESCREVENDO NO ARQUIVO OUT */
					fprintf(fileOut, "/");
					fprintf(fileOut, "%c", ultimoCaracter);	
				}
			}
		}else{
			/* ESCREVENDO NO ARQUIVO OUT */
			fprintf(fileOut, "%c", ultimoCaracter);	
		}
		ultimoCaracter = fgetc(fileIn);
	}
	 
	/* FECHANDO OS ARQUIVOS */
	fclose(fileIn);
	fclose(fileOut);
  
	return 0; 
} 