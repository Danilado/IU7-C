#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>

#define ROWMAX 10
#define COLMAX 10

typedef int matrix_t[ROWMAX][COLMAX];

#endif

size_t matrix_scan(matrix_t matrix, size_t rows, size_t columns);
