#include <stdio.h>
#include <math.h>

double serieLog(double z, int i);
double serieTgHip(double z, int i);

int main(void) {
  double z;
  int i, j;

  scanf("%lf %d %d", &z, &i, &j);

  printf("%.6lf %.6lf %.6lf\n", log(z), serieLog(z, i), serieTgHip(z, j));

  return 0;
}

double serieLog(double z, int i){
  int w;
  double resultado = 0;

  for(w = 1; w <= i; w++){
    if(w % 2 == 0){
      resultado -= (pow((z - 1), w))/(w);
    }else{
      resultado += (pow((z - 1), w))/(w);
    }
  }

  return resultado;
}

double serieTgHip(double z, int j){
  int w, indice = 1;
  double resultado = 0;
  
  for(w = 1; w <= j; w++){
    resultado += pow(((z-1)/(z+1)), indice)/indice;    
    indice += 2;
  }

  return (2 * resultado);
}