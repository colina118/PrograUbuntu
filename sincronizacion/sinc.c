#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char** argc)
{
  int i =0;
  int cont;
  int nthreads = 0;
  int tid;
  float arreglo[6];

  omp_set_nested(1);
  #pragma omp parrallel
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        #pragma omp critical
        {
          #pragma omp parallel num_threads(4) shared(cont, nthreads, tid)
          {
            nthreads = omp_get_num_threads();
            printf("NT: %d\n", nthreads);
            tid = omp_get_thread_num();
            printf("Num t: %d\n", tid);
            printf("i = %d\n", i);
            #pragma omp atomic
              cont++;
          }
        }
      }
      #pragma omp section
      {
        #pragma omp parallel num_threads(6) shared(i, arreglo, tid, nthreads)
        {
          tid = omp_get_thread_num();
          nthreads = omp_get_num_threads();
          arreglo[tid] = rand_r(&tid)%100;
        }
        float temp = 0;
        
        float prom = 1;
        for(i = 0; i < 6; i++)
        {
          printf("Pos %d valor = %f\n", i, arreglo[i]);
          temp += arreglo[i];
          prom = temp /6;
        }
        printf("Promedio: %f\nSumatiora: %f\n", prom, temp);
        printf("Iteraciones: %d\n", nthreads);
      }
    }
  }
}
