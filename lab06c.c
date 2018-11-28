#include <stdio.h>

int main(void) { 
  int i = 0, qtd = 0;
  char frase[81];

  fgets(frase, 81, stdin);

  /* printando a frase (incluindo paranteses) */
  while(frase[i] != '\0'){
    if(frase[i] == '(' && frase[i + 1] == '*'){
      i += 2;
    }
    if(frase[i] == '*' && frase[i + 1] == ')'){
      i += 2;
    }

    printf("%c", frase[i]);
    i++;
  }

  /* printando a frase sem os paranteses */
  i = 0;
  while(frase[i] != '\0'){
    if(frase[i] == '(' && frase[i + 1] == '*'){
      i += 2;
      while(frase[i] != '*' && frase[i + 1] != ')'){
        i++;
      }
      i += 2;
    }

    printf("%c", frase[i]);
    i++;
    qtd++;
  }

  printf("%d\n", qtd - 1);

  return 0;
}