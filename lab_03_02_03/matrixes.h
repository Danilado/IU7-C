#ifndef MATRIXES_H
#define MATRIXES_H

#include <stdio.h>

#define ROWMAX 10
#define COLMAX 10

typedef int matrix_t[ROWMAX][COLMAX];

#endif

size_t matrix_scan(matrix_t matrix, size_t rows, size_t columns);
void matrix_print(matrix_t matrix, size_t rows, size_t columns);

size_t matrix_remove_col(matrix_t matrix, size_t rows, size_t cols, size_t col);
