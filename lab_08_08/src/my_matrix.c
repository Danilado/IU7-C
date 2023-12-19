#include "my_matrix.h"

#ifndef NDEBUG
#include <assert.h>
#endif

int matrix_init(matrix_t *matrix, size_t rows, size_t columns)
{
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->rowsptr = malloc(sizeof(int32_t *) * rows);

    if (!matrix->rowsptr)
        return NOT_ENOUGH_MEMORY;

    for (size_t i = 0; i < matrix->rows; ++i)
    {
        matrix->rowsptr[i] = calloc(columns, sizeof(int32_t));
        if (!matrix->rowsptr[i])
            return NOT_ENOUGH_MEMORY;
    }

    return EXIT_SUCCESS;
}

int matrix_destroy(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; ++i)
        free(matrix->rowsptr[i]);
    free(matrix->rowsptr);

    return EXIT_SUCCESS;
}

int32_t matrix_get(const matrix_t *matrix, size_t row, size_t column)
{
#ifndef NDEBUG
    assert(row < matrix->rows);
    assert(column < matrix->columns);
#endif

    return matrix->rowsptr[row][column];
}

void matrix_set(matrix_t *matrix, size_t row, size_t column, int32_t value)
{
#ifndef NDEBUG
    assert(row < matrix->rows);
    assert(column < matrix->columns);
#endif

    matrix->rowsptr[row][column] = value;
}

int32_t matrix_row_min(const matrix_t *matrix, size_t row)
{
#ifndef NDEBUG
    assert(row < matrix->rows);
#endif

    int32_t min;
    min = matrix_get(matrix, row, 0);
    for (size_t j = 0; j < matrix->columns; ++j)
        if (matrix_get(matrix, row, j) < min)
            min = matrix_get(matrix, row, j);

    return min;
}

int32_t matrix_col_min(const matrix_t *matrix, size_t column)
{
#ifndef NDEBUG
    assert(column < matrix->columns);
#endif

    int32_t min;
    min = matrix_get(matrix, 0, column);
    for (size_t i = 0; i < matrix->rows; ++i)
        if (matrix_get(matrix, i, column) < min)
            min = matrix_get(matrix, i, column);

    return min;
}

int32_t matrix_col_geom_avg(const matrix_t *matrix, size_t column)
{
#ifndef NDEBUG
    assert(column < matrix->columns);
#endif

    double prod = 1;
    for (size_t i = 0; i < matrix->rows; ++i)
        prod *= abs(matrix_get(matrix, i, column));

    return (int32_t)pow(prod, 1.0 / matrix->rows);
}

void matrix_copy(const matrix_t *src, matrix_t *dst)
{
    for (size_t i = 0; i < MIN(src->rows, dst->rows); ++i)
        memcpy(dst->rowsptr[i], src->rowsptr[i],
        sizeof(int32_t) * MIN(src->columns, dst->columns));
}

int matrix_scanf(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; ++i)
        for (size_t j = 0; j < matrix->columns; ++j)
        {
            int32_t tmp;
            if (scanf("%" SCNd32, &tmp) != 1)
                return SCANF_ERROR;
            matrix_set(matrix, i, j, tmp);
        }

    return EXIT_SUCCESS;
}

void matrix_print(const matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; ++i)
    {
        for (size_t j = 0; j < matrix->columns; ++j)
            printf("%" PRId32 " ", matrix_get(matrix, i, j));
        printf("\n");
    }
}

void matrix_get_min_coords(const matrix_t *matrix, size_t *row, size_t *column)
{
    int32_t min = matrix_get(matrix, 0, 0);
    *row = 0;
    *column = 0;

    for (size_t j = 0; j < matrix->columns; ++j)
        for (size_t i = 0; i < matrix->rows; ++i)
        {
            int32_t tmp = matrix_get(matrix, i, j);
            if (tmp <= min)
            {
                min = tmp;
                *row = i;
                *column = j;
            }
        }
}

int matrix_squarify(matrix_t *matrix)
{
    if (matrix->rows == matrix->columns)
        return EXIT_SUCCESS;

    size_t target_n = MIN(matrix->rows, matrix->columns);

    while (matrix->rows != target_n || matrix->columns != target_n)
    {
        size_t minr, minc;
        matrix_get_min_coords(matrix, &minr, &minc);
        if (matrix->rows > matrix->columns)
            matrix_row_remove(matrix, minr);
        else
            matrix_col_remove(matrix, minc);
    }

    return EXIT_SUCCESS;
}

void matrix_row_remove(matrix_t *matrix, size_t row)
{
#ifndef NDEBUG
    assert(row < matrix->rows);
    assert(matrix->rows > 0);
#endif

    for (size_t i = row; i < matrix->rows - 1; ++i)
    {
        memmove(matrix->rowsptr[i], matrix->rowsptr[i + 1],
        sizeof(int32_t) * matrix->columns);
    }

    free(matrix->rowsptr[matrix->rows - 1]);
    --matrix->rows;
}

void matrix_col_remove(matrix_t *matrix, size_t column)
{
#ifndef NDEBUG
    assert(column < matrix->columns);
    assert(matrix->columns > 0);
#endif

    if (column != matrix->columns - 1)
        for (size_t i = 0; i < matrix->rows; ++i)
            memmove(&matrix->rowsptr[i][column],
            &matrix->rowsptr[i][column + 1],
            sizeof(int32_t) * (matrix->columns - column - 1));
    --matrix->columns;
}

int matrix_row_add(matrix_t *matrix)
{
    matrix_t tmp;
    int rc;
    rc = matrix_init(&tmp, matrix->rows + 1, matrix->columns);
    if (rc)
        return rc;

    matrix_copy(matrix, &tmp);

    for (size_t j = 0; j < matrix->columns; ++j)
        matrix_set(&tmp, matrix->rows, j, matrix_col_geom_avg(matrix, j));

    matrix_destroy(matrix);
    *matrix = tmp;

    return EXIT_SUCCESS;
}

int matrix_col_add(matrix_t *matrix)
{
    matrix_t tmp;
    int rc;
    rc = matrix_init(&tmp, matrix->rows, matrix->columns + 1);
    if (rc)
        return rc;

    matrix_copy(matrix, &tmp);

    for (size_t i = 0; i < matrix->rows; ++i)
        matrix_set(&tmp, i, matrix->columns, matrix_row_min(matrix, i));

    matrix_destroy(matrix);
    *matrix = tmp;

    return EXIT_SUCCESS;
}

int matrix_unify(matrix_t *m1, matrix_t *m2)
{
    int rc;
    size_t target_size = MAX(m1->rows, m2->rows);

    while (m1->rows != target_size || m2->rows != target_size)
    {
        if (m1->rows < m2->rows)
            rc = matrix_row_add(m1);
        else
            rc = matrix_row_add(m2);

        if (rc)
            return rc;
    }

    while (m1->columns != target_size || m2->columns != target_size)
    {
        if (m1->columns < m2->columns)
            rc = matrix_col_add(m1);
        else
            rc = matrix_col_add(m2);

        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

// dst should not be initialized
int matrix_mul(const matrix_t *m1, const matrix_t *m2, matrix_t *dst)
{
    int rc;
    rc = matrix_init(dst, m1->rows, m2->columns);
    if (rc)
        return rc;

    for (size_t i = 0; i < m1->rows; ++i)
        for (size_t j = 0; j < m2->columns; ++j)
        {
            int32_t sum = 0;
            for (size_t k = 0; k < m1->columns; ++k)
                sum += matrix_get(m1, i, k) * matrix_get(m2, k, j);
            matrix_set(dst, i, j, sum);
        }

    return EXIT_SUCCESS;
}

// not in .h (only used in matrix_pow)
int matrix_zero_pow(const matrix_t *matrix, matrix_t *dst)
{
#ifndef NDEBUG
    assert(matrix->columns == matrix->rows);
#endif

    int rc;
    rc = matrix_init(dst, matrix->columns, matrix->columns);
    if (rc)
        return rc;

    for (size_t i = 0; i < dst->rows; ++i)
        matrix_set(dst, i, i, 1);

    return EXIT_SUCCESS;
}

// dst should not be initialized
int matrix_pow(const matrix_t *matrix, size_t power, matrix_t *dst)
{
    if (matrix->columns != matrix->rows)
        return SIZE_MISMATCH;

    if (power == 0)
        return matrix_zero_pow(matrix, dst);

    if (power == 1)
    {
        matrix_init(dst, matrix->rows, matrix->columns);
        matrix_copy(matrix, dst);
        return EXIT_SUCCESS;
    }

    matrix_t tmp1, tmp2;
    size_t tmppow = 1;
    int rc;

    matrix_init(&tmp1, matrix->rows, matrix->columns);

    matrix_copy(matrix, &tmp1);

    while (tmppow * 2 <= power)
    {
        rc = matrix_mul(&tmp1, &tmp1, &tmp2);
        if (rc)
            return rc;

        matrix_copy(&tmp2, &tmp1);
        matrix_destroy(&tmp2);

        tmppow *= 2;
    }

    // делишос
    rc = matrix_pow(matrix, power - tmppow, &tmp2);
    if (rc)
        return rc;

    rc = matrix_mul(&tmp1, &tmp2, dst);
    if (rc)
        return rc;

    matrix_destroy(&tmp1);
    matrix_destroy(&tmp2);

    return EXIT_SUCCESS;
}
