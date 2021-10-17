//Без звездочки
#include <stdio.h>
#include "omp.h"

#define array_size 100000

void writeResultIntoFile(double *b) {
    FILE *out;
    out = fopen("out.txt", "w");

    fprintf(out, "Processed array: [");
    for (int i = 0; i < array_size - 1; ++i) {
        fprintf(out, "%.2f ",b[i]);
    }
    fprintf(out, "%.2f]",b[array_size - 1]);
    fclose(out);
}

//! Prints processed array into console or "out.txt" file
//! \param tmp array to print
//! \param where (0 - console, else - "out.txt" file)
void printResult(double *tmp, int where) {
    if (where == 0) {
        printf("Processed array: [");
        for (int i = 0; i < array_size - 1; ++i) {
            printf("%.2f ", tmp[i]);
        }
        printf("%.2f]\n", tmp[array_size - 1]);
    }
    else {
        writeResultIntoFile(tmp);
    }
}

int main() {
    //!Filling initial array
    double a[array_size];
    for (int i = 0; i < array_size; ++i) {
        a[i] = i;
    }
    
    //!Creating tmp array and filling border its values(tmp[0], tmp[array_size - 1]
    double tmp[array_size];
    tmp[0] = 0;
    tmp[array_size - 1] = array_size - 1;

    //!For cycle with dynamic schedule to balance process by thread load
    #pragma omp parallel for schedule(dynamic)
    for (int i = 1; i < array_size - 1; ++i) {
        tmp[i] = (a[i - 1] * a[i] * a[i + 1]) / 3.0;
    }

    /*printf("Initial array: [");
    for (int i = 0; i < array_size - 1; ++i) {
        printf("%.2f ", a[i]);
    }
    printf("%.2f]\n", a[array_size - 1]);
     */
    printResult(tmp, 1);
    return 0;
}
