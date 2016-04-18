#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char** argc)
{
  float posiciones** = (float**)malloc(5000*sizeof(float));
  float centro* = (float*)malloc(5000*sizeof(float));

  float x1, x2, y1, y2;
  int i, j, sumax1, sumay1, sumax2, sumay2, cont1, cont2;

  while(x1 < .0001 && y1 < .0001 && x2 < .0001 && y2 < .0001)
  {

    #pragma omp parallel shared(posiciones, distancias, centro, x1, x2, y1, y2, i, j)
    {
      int tid = omp_get_thread_num();
      int d1, d2;
      x1 = rand_r(&tid)%5;
      x2 = rand_r(&tid)%5;
      y1 = rand_r(&tid)%5;
      y2 = rand_r(&tid)%5;
      #pragma omp for schedule(auto)
      for(i = 0; i < 5000; i++)
      {
        d1 = 0;
        d2 = 0;
        posiciones[i]=(float*)malloc(2 * sizeof(float));
        for(j = 0; j < 2;  j++)
        {
          posiciones[i][j]=rand_r(&tid)%5;
        }
        d1=sqrt(pow(posiciones[i][0]-x1)+pow(posiciones[i][1]-y1));
        d2=sqrt(pow(posiciones[i][0]-x2)+pow(posiciones[i][1]-y2));
        if(d1 < d2)
        {
          centro[i]=1;
        }
        else if(d2 < d1)
        {
          centro[i]=2;
        }
      }
    }
    #pragma omp parallel shared(posiciones, distancias, centro, x1, x2, y1, y2, i, j, sumax1, sumay1, cont1, cont2)
    {
      #pragma omp for schedule(auto)
      for(i = 0; i < 5000; i++)
      {
        if(centro[i] == 1)
        {
          sumax1 += posiciones[i][0];
          sumay1 += posiciones[i][1];
          cont1++;
        }
        else if(centro[i] == 2)
        {
          sumax2 += posiciones[i][0];
          sumay2 += posiciones[i][1];
          cont2++;
        }
      }
      #pragma omp barrier
    }
    x1 = sumax1/cont1;
    y1 = sumay1/cont1;
    x2 = sumax2/cont2;
    y2 = sumay2/cont2;

    printf("Las coordenadas del centro 1 son x= %f y= %f\n", x1, y1);
    printf("Las coordenadas del centro 2 son x= %f y= %f\n", x2, y2);
  }
}
