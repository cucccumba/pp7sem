#include <stdio.h>
#include "omp.h"

int main() {
    #pragma omp parallel
    {
        for (int i = omp_get_num_threads() - 1; i >= 0; --i) {
            #pragma omp barrier
            {
                if (i == omp_get_thread_num()) {
                    printf("Thread #%d\n", i);
                }
            }
        }
    }
    return 0;
}
