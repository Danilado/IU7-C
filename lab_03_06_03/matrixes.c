#include "./matrixes.h"

#include <stdlib.h>

void matrix_print(matrix_t matrix, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}
