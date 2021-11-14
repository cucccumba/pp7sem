/******************************************************************************
* ЗАДАНИЕ: bugged2.c
* ОПИСАНИЕ:
*   Еще одна программа на OpenMP с багом.
******************************************************************************/

#include <omp.h>
#include <stdio.h>
//#include <stdlib.h>

int main(int argc, char **argv)
{
    int nthreads, i, tid;
    //float total;
    double total = 0.0; //it is better to initialize variable out of parallel section and make it double

    #pragma omp parallel private(tid) //need to make tid variable private
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d is starting...\n", tid);
        #pragma omp barrier
        {}
        //total = 0.0;
        #pragma omp for schedule(dynamic, 10) reduction(+:total) //reduction to get rid of threads race
        for (i = 0; i < 1000000; i++) {
            total = total + i * 1.0;
        }


        printf ("Thread %d is done! Total= %e\n", tid, total);
    }
}
