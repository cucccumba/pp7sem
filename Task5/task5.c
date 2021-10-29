// С звездочкой

#include <stdio.h>
#include "omp.h"

#define N 20 //! number of terms in the sum
#define x 1.570796 //! argument

//! Count factorial
double get_factorial(int a) {
    if (a == 0) {
        return 1.0;
    }
    double res = 1;
    for (int i = 2; i <= a; ++i) {
        res *= i;
    }
    return res;
}
//! Count a^pow
double get_pow(double a, int pow) {
    if (pow == 0) {
        return 1.0;
    }
    double res = 1;
    for (int i = 0; i < pow; ++i) {
        res *= a;
    }
    return res;
}
//! Count n partial sum of series sin(a)
//! Get n! counted previously and calculate (2n + 1)!
double get_sin(double a, double factorial_n, int n) {
    double denam = factorial_n;
    for (int i = n + 1; i <= 2 * n + 1; ++i) {
        denam *= i;
    }
    double res = get_pow(a, 2 * n + 1) / denam;
    if (n % 2 != 0) {
        res *= -1;
    }
    return res;
}

//! (e^x)*six(x) = sum{(x^n / n!) * ((-1)^n * x^(2n + 1) / (2n + 1)!)}
int main() {
    double result_e = 0;
    double result_sin = 0;
    #pragma omp parallel for
    for (int i = 0; i <= N; ++i) {
        double factorial_n = get_factorial(i);
        double res_e = get_pow(x, i) / factorial_n;
        double res_sin = get_sin(x, factorial_n, i);
        #pragma omp critical
        {
            result_e += res_e;
            result_sin += res_sin;
        }
    }
    printf("e^(%f) * sin(%f) =  %f\n", (x), (x),  result_e * result_sin);
}
