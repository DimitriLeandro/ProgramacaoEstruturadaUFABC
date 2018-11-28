#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ra, telefone;
    char nome[100];
} Aluno;

typedef struct {
    int armazenados;
    int capacidade;
    Aluno *alunos;
} Base;

/* Cria uma base nova que armazena 0 alunos mas tem capacidade para n, alocando
 * essa quantidade de alunos.
 * Imprime "Base criada.\n" no fim */
void criar_base(Base *base, int n) {
    (*base).armazenados = 0;
    (*base).capacidade = n;
    (*base).alunos = malloc(n * sizeof(Aluno));
    printf("Base criada.\n");
}

/* Procura por aluno ra na base
 * Retorna a posição do aluno no vetor alunos caso ele exista
 * Retorna -1 caso contrário */
int buscar(Base *base, int ra) {
    int i;
    for(i = 0; i < (*base).capacidade; i++){
        if((*base).alunos[i].ra == ra){
            return i;
        }
    }
    return -1;
}

/* Imprime a informação de um aluno.
 * Se o aluno ra existe na base, imprime "RA - TELEFONE - NOME\n"
 * Caso contrário imprime "Aluno RA nao encontrado.\n" */
void imprimir(Base *base, int ra) {
    int indexAluno  = buscar(base, ra);
    if(indexAluno == -1){
        printf("Aluno %d nao encontrado.\n", ra);
    }else{
        printf("%d - %d - %s\n", ra, (*base).alunos[indexAluno].telefone, (*base).alunos[indexAluno].nome);
    }
}

/* Tenta adicionar um novo aluno na base.
 * Se a base está cheia, não faz nada e imprime "Erro: base cheia.\n"
 * Se a base não está cheia e o aluno não existe ainda na base, adiciona ele e
 * imprime "Adicionado: RA - TELEFONE - NOME\n" 
 * Se a base não está cheia e o aluno existe, altera seus dados e imprime
 * "Alterado: RA - TELEFONE - NOME\n" */
void adicionar(Base *base, int ra, int telefone, char *nome) {
    int indexAluno, primeiroIndexVazio, k;

    indexAluno = buscar(base, ra);
    
    /* SE O ALUNO JA EXISTE */
    if(indexAluno != -1){
        (*base).alunos[indexAluno].telefone = telefone;
        strcpy((*base).alunos[indexAluno].nome, nome);
        printf("Alterado: %d - %d - %s\n", ra, telefone, nome);
    }
    /* SENAO CADASTRA */
    else{
        /* SO POSSO CADASTRAR SE A BASE NAO ESTIVER CHEIA */
        if((*base).armazenados == (*base).capacidade){
            printf("Erro: base cheia.\n");
        }else{
            /*  EU POSSO TER EXCLUIDO ALGUEM E DEIXADO ELE COM RA -2 
                ENTAO VOU VER QUAL E O INDEX DO ALUNO QUE DA PRA CADASTRAR PQ TA VAZIO 
                SE NAO TIVER NENHUM VAZIO, ENTAO O INDEX VAI SER armazenados */
            primeiroIndexVazio = (*base).armazenados;
            for(k = 0; k < (*base).armazenados; k++){
                if((*base).alunos[k].ra == -2){
                    primeiroIndexVazio = k;
                    break;
                }
            }

            /* COLOCANDO OS DADOS */
            (*base).alunos[primeiroIndexVazio].ra = ra;
            (*base).alunos[primeiroIndexVazio].telefone = telefone;
            strcpy((*base).alunos[primeiroIndexVazio].nome, nome);

            /* ALTERANDO O NUMERO DE ARMAZENADOS */
            (*base).armazenados = (*base).armazenados + 1;

            printf("Adicionado: %d - %d - %s\n", ra, telefone, nome);
        }
    }           
}

/* Tenta remover um aluno da base.
 * Se o aluno existe na base, remove-o e imprime "Aluno RA removido.\n"
 * Se o aluno não existe, imprime "Aluno RA nao encontrado.\n" */
void remover(Base *base, int ra) {
    int indexAluno;
    indexAluno = buscar(base, ra);
    
    /* SE NAO ENCONTROU */
    if(indexAluno == -1){
        printf("Aluno %d nao encontrado.\n", ra);
    }
    /* SE ENCONTROU ENTAO JOGA O RA PRA -2 E DIMINUI O NUMERO DE ARMAZENADOS */
    else{
        (*base).armazenados = (*base).armazenados - 1;
        (*base).alunos[indexAluno].ra = -2;
        printf("Aluno %d removido.\n", ra);
    }

}

/* Reseta os valores da base para 0 ou NULL, liberando a memória alocada */
void liberar_base(Base *base) {
    free((*base).alunos);
    (*base).armazenados = 0;
    (*base).capacidade = 0;
    (*base).alunos = NULL;
}