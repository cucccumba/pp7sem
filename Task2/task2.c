#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(int argc, char *argv[]) {
    int res = 0;
    int N = atoi(argv[1]);
    #pragma omp parallel for schedule(static) reduction(+:res)
    for(int i = 1; i <= N; ++i) {
        res = res + i;
        printf("Thread #%d: sum = %d\n", omp_get_thread_num(), res);
    }
    printf("Result: %d\n", res);
    return 0;
}
