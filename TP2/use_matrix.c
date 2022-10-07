#include <stdio.h>
#include "matrix.h"

int main() {
    matrix *mymatrix = matrix_new(10, 10);
    matrix *craptrix = matrix_new_random(10, 9, -9, 10);
    double value = matrix_get(457, 875, craptrix);
    printf("rand value %lf\n", value);
    matrix *top10matrices = matrix_add(mymatrix, craptrix);
    matrix_print(top10matrices);
}