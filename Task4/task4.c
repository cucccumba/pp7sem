// Без звездочки
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

/*!
 * Fills matrix with numbers
 * @param matrix
 * @param r number of rows
 * @param c number of columns
 * @param isRandom numbers to fill with (isRandom > 0 - Random numbers, isRandom <= 0 - fills with 0)
 */
void fillMatrix(int **matrix, int r, int c, int isRandom) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if (isRandom) {
                matrix[i][j] = rand() % 100;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
}

void printMatrix(int **matrix, int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            printf("%d ", matrix[i][j]);
        }
        if (i != r - 1) {
            printf("\n");
        }
    }
}

int main() {
    int r1 = 3; //!number of rows in A matrix
    int c1 = 3; //!number of columns in A matrix
    int r2 = 3; //!number of rows in B matrix
    int c2 = 3; //!number of columns in B matrix

    int **matrix1 = (int**)malloc(sizeof(int*)*r1);
    for(int i = 0; i < r1; i++) {
        matrix1[i] = (int*)malloc(sizeof(int)*c1);
    }
    int **matrix2 = (int**)malloc(sizeof(int*)*r2);
    for(int i = 0; i < r2; i++) {
        matrix2[i] = (int*)malloc(sizeof(int)*c2);
    }
    int **result = (int**)malloc(sizeof(int*)*r1);
    for(int i = 0; i < r1; i++) {
        result[i] = (int*)malloc(sizeof(int)*c2);
    }

    fillMatrix(matrix1, r1, c1, 1);
    fillMatrix(matrix2, r2, c2, 1);
    fillMatrix(result, r1, c2 ,0);

    #pragma omp parallel for
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }

    printf("-----------------------------------------------\n");
    printf("Matrix1:\n");
    printMatrix(matrix1, r1, c1);
    printf("\n-----------------------------------------------\n");
    printf("Matrix2:\n");
    printMatrix(matrix2, r2, c2);
    printf("\n-----------------------------------------------\n");
    printf("Result:\n");
    printMatrix(result, r1, c2);
    printf("\n-----------------------------------------------\n");
    return 0;
}
