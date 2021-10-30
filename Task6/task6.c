// С звездочкой

#include <stdio.h>
#include "omp.h"

#define N 1000

//! The algorithm used is the sieve of eratosthenes
//! There is an array of numbers: 2 to N, in the process of algorithm all sifted numbers will be replaced with '0'
int main() {
    int a[N - 1];
    for (int i = 0; i < N - 1; ++i) {
        a[i] = i + 2;
    }

    int current = 2; //! not sifted number to compare to other numbers
    // sifting numbers
    do {
        #pragma parallel for
        {
            for (int i = 1; i < N - 1; ++i) {
                if (a[i] == current) {
                    continue;
                }
                // if number not sifted and it is divisible by current mark as not prime number (replace with '0')
                if (a[i] != 0 && a[i] % current == 0) {
                    #pragma omp critical
                    {
                        a[i] = 0;
                    }
                }
            }
        }
        // Looking for next not sifted number to compare
        #pragma parallel for
        {
            for (int i = current - 1; i < N - 1; ++i) {
                if (a[i] != 0) {
                    current = a[i];
                    break;
                }
                // In case if all numbers greater, then current not prime (need to end cycle)
                if (i == N - 2) {
                    current = N;
                }
            }
        }
    }
    while (current != N);

    for (int i = 0; i < N - 1; ++i) {
        if (a[i] != 0) {
            printf("%d ", a[i]);
        }
    }
    return 0;
}
