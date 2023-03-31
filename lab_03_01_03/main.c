/*
По матрице получить и вывести на экран одномерный массив, присвоив его 𝑘-
тому элементу значение 1, если выполняется указанное условие, и значение 0 в
иных случаях: лементы 𝑘-ой строки образуют монотонную последовательность
*/

#include "./matrixes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4
#define MATRIX_EL_INPUT_ERROR 5

#define NMAX 10

typedef int arr_t[NMAX];

bool is_monotonous(int *ps, int *pe)
{
    if (pe - ps < 2)
        return false;
    // алгоритмически обработка разницы между
    // сосеними элементами сложнее, чем мой способ,
    // т.к. пришлось бы сохранять старый знак, когда
    // элементы равны
    bool notdec = true;
    bool notinc = true;

    for (int *pcur = ps + 1; (pcur < pe) && (notinc || notdec); ++pcur)
    {
        if (*(pcur - 1) < *pcur)
            notinc = false;
        if (*(pcur - 1) > *pcur)
            notdec = false;
    }

    return notinc || notdec;
}

void form_answer(arr_t arr, matrix_t matrix, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
        arr[i] = is_monotonous(matrix[i], matrix[i] + columns);
}

void arr_print(int *ps, int *pe)
{
    for (int *pcur = ps; pcur < pe; ++pcur)
        printf("%d ", *pcur);
    printf("\n");
}

int main(void)
{
    matrix_t matrix;
    arr_t answer;
    size_t rows, columns;

    printf("Введите количество строк и столбцов матрицы: ");
    if (scanf("%zu", &rows) != 1)
    {
        puts("Ошибка ввода количества строк");
        return ROW_COUNT_INPUT_ERROR;
    }
    if (rows == 0 || rows > 10)
    {
        puts("Неверно введено количество строк");
        return BAD_ROW_COUNT_ERROR;
    }

    if (scanf("%zu", &columns) != 1)
    {
        puts("Ошибка ввода количества столбцов");
        return COL_COUNT_INPUT_ERROR;
    }
    if (columns == 0 || columns > 10)
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

    form_answer(answer, matrix, rows, columns);

    printf("Результат: ");
    arr_print(answer, answer + rows);

    return EXIT_SUCCESS;
}
