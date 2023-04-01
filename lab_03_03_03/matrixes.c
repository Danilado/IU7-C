#include "./matrixes.h"

#include <stdlib.h>

size_t matrix_scan(matrix_t matrix, size_t rows, size_t columns)
{
    size_t el_count = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return el_count;
            ++el_count;
        }

    return el_count;
}

void matrix_print(matrix_t matrix, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}
