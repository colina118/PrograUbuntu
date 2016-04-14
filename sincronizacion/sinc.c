#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char** argc)
{
  int i =0;
  int cont;
  int nthreads = 0;
  int tid;
  int arreglo[6];
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
        #pragma omp parallel num_threads(6) shared(i, arreglo, tid)
        {
          tid = omp_get_thread_num();
          arreglo[tid] = rand_r(&tid)%100;
        }
        int temp = 0;
        for(i = 0; i < 6; i++)
        {
          printf("Pos %d valor = %d\n", i, arreglo[i]);
          temp += arreglo[i];
        }
      }
    }
  }
}
