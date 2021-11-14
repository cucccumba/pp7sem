//!To enter array from keyboard write an option argument -a
//!To enter array from file write it in "input.txt" file

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "omp.h"

int getArraySizeFromFile(char *fileName) {
    FILE *inFile = fopen(fileName, "r");
    if (inFile == NULL) {
        printf("File not found\n");
        exit(1);
    }
    int size = 0;
    int k = 0;
    while(fscanf(inFile, "%d", &k) != EOF) {
        ++size;
    }
    fclose(inFile);
    return size;
}

int32_t* getArrayFromFile(char *fileName, int32_t *array, int size) {
    FILE *inFile = fopen(fileName, "r");
    if (inFile == NULL) {
        printf("File not found\n");
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        fscanf(inFile, "%d", &(array[i]));
    }
    return array;
}

void qsortRecursive(int *mas, int size) {
    int i = 0;
    int j = size - 1;
    int mid = mas[size / 2];
    do {
        //keep elements on the left side that are less than the middle one
        while(mas[i] < mid) {
            i++;
        }
        //keep elements on the right side that are greater than the middle one
        while(mas[j] > mid) {
            j--;
        }
        //swap elements
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    //send recursive calls to tasks
    #pragma omp task shared(mas)  //left side
    {
        if(j > 0) {
            qsortRecursive(mas, j + 1);
        }
    }
    #pragma omp task shared(mas)  //right side
    {
        if (i < size) {
            qsortRecursive(&mas[i], size - i);
        }
    }
    #pragma omp taskwait
}

int checkSortedBackwards(const int32_t *array, int size) {
    for(int i = size - 1; i >= 1; --i) {
        if (array[i] < array[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv) {
    //getting array
    int flag;
    int is_Cmd = 0;
    while((flag = getopt(argc, argv, "a")) != -1) {
        if (flag == 'a') {
            is_Cmd = 1;
        }
    }
    int32_t *array = NULL;
    int size = 0;
    if (is_Cmd) {
        array = (int32_t *) malloc(10 * sizeof(int32_t));
        size = 0;
        printf("Enter array\n");
        while (scanf("%d", &array[size]) == 1) {
            ++size;
        }
    }
    else {
        size = getArraySizeFromFile("input.txt");
        array = (int32_t*) malloc(size * sizeof(int32_t));
        array = getArrayFromFile("input.txt", array, size);
    }

    //sorting array
    if (size == 1) {
        printf("%d\n", array[0]);
        return 0;
    }
    if (checkSortedBackwards(array, size)) {
        for (int i = size - 1; i >= 0; --i) {
            printf ("%d ", array[i]);
        }
        printf("\n");
        return 0;
    }
    qsortRecursive(array, size);
    for (int i = 0; i < size; ++i) {
        printf ("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
