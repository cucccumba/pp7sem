/******************************************************************************
* ЗАДАНИЕ: bugged6.c
* ОПИСАНИЕ:
*   Множественные ошибки компиляции
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod(const float res)
{
    int i, tid;
    float sum = res;
    tid = omp_get_thread_num();
    //need to define parallel for or put #pragma omp for inside #pragma omp parallel shared(sum)
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < VECLEN; i++)
    {
        sum = sum + (a[i] * b[i]);
        printf("  tid= %d i=%d\n", tid, i);
    }
    return sum;
}


int main (int argc, char *argv[])
{
    int i;
    float sum;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;
    sum = 0.0;

    //It is better to define parallel section inside function
    //Variable sum will not be transferred to function and returned via shared(sum). It should be done explicitly
    //#pragma omp parallel shared(sum)
    sum = dotprod(sum);

    printf("Sum = %f\n",sum);
}


