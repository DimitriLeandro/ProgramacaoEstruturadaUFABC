#include <stdio.h>

void converter(int num, int base);

int main(void) {  
  int x, y;

  scanf("%d %d", &x, &y);

  converter(x, y);

  return 0;
}

void converter(int num, int base){
  while(num >= base){
    printf("%d", num % base);
    num /= base;
  }
  printf("%d\n", num);
}