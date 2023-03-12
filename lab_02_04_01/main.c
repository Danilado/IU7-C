#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define EMPTY_ARRAY_ERROR 1
#define FULL_ARRAY_ERROR 100

typedef double arr[NMAX];

void insertion_sort(arr a, size_t alen)
{
    double tmp;
    size_t j;

    for (size_t i = 1; i < alen; ++i)
    {
        j = i;
        tmp = a[j];
        while (j > 0 && tmp < a[j - 1])
        {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = tmp;
    }

    return;
}

int main(void)
{
    arr a;
    double tmp;
    size_t alen = 0;
    bool full_arr_flag = 0;

    printf("Введите элемент массива: ");
    for (size_t i = 0; scanf("%lf", &tmp) == 1; ++i)
    {
        if (alen == NMAX)
        {
            full_arr_flag = 1;
            break;
        }
        a[i] = tmp;
        printf("Введите элемент массива: ");
        ++alen;
    }

    if (!alen)
    {
        printf("Введите хотя бы один элемент!\n");
        return EMPTY_ARRAY_ERROR;
    }

    insertion_sort(a, alen);

    printf("Отсортированный массив: ");
    for (size_t i = 0; i < alen; ++i)
        printf("%.6lf ", a[i]);
    printf("\n");

    if (full_arr_flag)
        return FULL_ARRAY_ERROR;

    return EVERYTHING_OK;
}
