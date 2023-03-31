#pragma once

#include <stdio.h>

#define ROWMAX 10
#define COLMAX 10

typedef int matrix_t[ROWMAX][COLMAX];

size_t matrix_scan(matrix_t matrix, size_t rows, size_t columns);
void matrix_print(matrix_t matrix, size_t rows, size_t columns);
void transpond(matrix_t dstmat, matrix_t srcmat, size_t r, size_t c);
void transpond_in_place(matrix_t matrix, size_t rows, size_t columns);
void int_swap(int *first, int *second);
