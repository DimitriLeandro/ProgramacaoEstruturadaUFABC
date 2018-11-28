#include <stdio.h>

double area(double a[2], double b[2], double c[2]);

int main(void) {  

  int qtdVertices, i;
  double a[2], b[2], c[2], areaTotal;

  do{
    scanf("%d", &qtdVertices);
    if(qtdVertices > 0){
      areaTotal = 0;
      for(i = 1; i <= (qtdVertices * 2); i++){
        /* SE I FOR IMPAR, TA LENDO A COORDENADA X, SE FOR PAR, TA LENDO A Y*/
        if(i <= 2){
          scanf("%lf", &a[i - 1]);
        } else {
          if(i % 2 != 0){
            b[0] = c[0];
            scanf("%lf", &c[0]);
          }else{
            b[1] = c[1];
            scanf("%lf", &c[1]);
            if(i >= 6){
              areaTotal += area(a, b, c);
            }
          }   
        }    
      }
      printf("%.6f\n", areaTotal);
    }
  }while(qtdVertices > 0);

  return 0;
}

double area(double a[2], double b[2], double c[2]){
  double aux;

  aux = (1.0/2.0) * ((a[0] * b[1]) + (a[1] * c[0]) + (b[0] * c[1]) - ((a[1] * b[0]) + (a[0] * c[1]) + (b[1] * c[0])));

  if(aux < 0){
    aux *= -1;
  }
  
  return aux;
}