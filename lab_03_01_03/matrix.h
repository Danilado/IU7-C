#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

#define ROWMAX 10
#define COLMAX 10

typedef int matrix_t[ROWMAX][COLMAX];

size_t matrix_scan(matrix_t matrix, size_t rows, size_t columns);

#endif
