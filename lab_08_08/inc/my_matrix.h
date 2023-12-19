#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <inttypes.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_utils.h"

typedef struct
{
    int32_t **rowsptr;
    size_t rows;
    size_t columns;
} matrix_t;

enum matrix_errors
{
    NOT_ENOUGH_MEMORY = 1,
    OUT_OF_BOUNDS,
    SCANF_ERROR,
    SIZE_MISMATCH,
};

int matrix_init(matrix_t *matrix, size_t rows, size_t columns);
int matrix_destroy(matrix_t *matrix);

int matrix_scanf(matrix_t *matrix);
void matrix_print(const matrix_t *matrix);

int32_t matrix_get(const matrix_t *matrix, size_t row, size_t column);
void matrix_set(matrix_t *matrix, size_t row, size_t column, int32_t value);

int32_t matrix_row_min(const matrix_t *matrix, size_t row);
int32_t matrix_col_min(const matrix_t *matrix, size_t column);

int32_t matrix_col_geom_avg(const matrix_t *matrix, size_t column);
void matrix_copy(const matrix_t *src, matrix_t *dst);

int matrix_squarify(matrix_t *matrix);
int matrix_unify(matrix_t *m1, matrix_t *m2);

void matrix_row_remove(matrix_t *matrix, size_t row);
void matrix_col_remove(matrix_t *matrix, size_t column);

int matrix_row_add(matrix_t *matrix);
int matrix_col_add(matrix_t *matrix);

int matrix_mul(const matrix_t *m1, const matrix_t *m2, matrix_t *dst);
int matrix_pow(const matrix_t *matrix, size_t power, matrix_t *dst);

#endif
