#include "./arrays.h"
#include "./matrixes.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4
#define MATRIX_EL_INPUT_ERROR 5
#define NO_TEN_DIGIT_SUM_ELS_ERROR 6

#define ELS_TO_SHIFT 3

int digit_sum(int num)
{
    int sum = 0;
    num = abs(num);
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

size_t filter_digsum_elements(arr_t dst, matrix_t src, size_t r, size_t c)
{
    size_t dstlen = 0;

    for (size_t i = 0; i < r; ++i)
        for (size_t j = 0; j < c; ++j)
            if (digit_sum(src[i][j]) > 10)
            {
                dst[dstlen] = src[i][j];
                ++dstlen;
            }

    return dstlen;
}

void put_digsum_elements(arr_t src, size_t slen, matrix_t dst, size_t cols)
{
    size_t scur = 0;

    for (size_t i = 0; scur < slen; ++i)
        for (size_t j = 0; j < cols && scur < slen; j++)
            if (digit_sum(dst[i][j]) > 10)
            {
                dst[i][j] = src[scur];
                ++scur;
            }
}

int main(void)
{
    matrix_t matrix;
    arr_t numbers;
    size_t rows, columns, numlen;

    printf("Введите количество строк и столбцов матрицы: ");
    if (scanf("%zu", &rows) != 1)
    {
        puts("Ошибка ввода количества строк");
        return ROW_COUNT_INPUT_ERROR;
    }
    if (rows == 0 || rows > ROWMAX)
    {
        puts("Неверно введено количество строк");
        return BAD_ROW_COUNT_ERROR;
    }

    if (scanf("%zu", &columns) != 1)
    {
        puts("Ошибка ввода количества столбцов");
        return COL_COUNT_INPUT_ERROR;
    }
    if (columns == 0 || columns > COLMAX)
    {
        puts("Неверно введено количество столбцов");
        return BAD_COL_COUNT_ERROR;
    }

    printf("Введите матрицу: \n");
    if (matrix_scan(matrix, rows, columns) != rows * columns)
    {
        puts("Ошибка ввода элемента матрицы");
        return MATRIX_EL_INPUT_ERROR;
    }

    numlen = filter_digsum_elements(numbers, matrix, rows, columns);

    if (!numlen)
    {
        puts("В матрице нет элементов с суммой цифр больше 10");
        return NO_TEN_DIGIT_SUM_ELS_ERROR;
    }

    arr_shift_left(numbers, numlen, ELS_TO_SHIFT);

    put_digsum_elements(numbers, numlen, matrix, columns);

    printf("Полученная матрица:\n");
    matrix_print(matrix, rows, columns);

    return EXIT_SUCCESS;
}
