#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define EMPTY_ARRAY_ERROR 1
#define FULL_ARRAY_ERROR 100

typedef int arr[NMAX];

size_t scan_arr(arr a)
{
    size_t alen = 0;
    int tmp;
    printf("Введите элемент массива: ");
    for (size_t i = 0; scanf("%d", &tmp) == 1; ++i)
    {
        if (alen == NMAX)
            return NMAX + 1;

        a[i] = tmp;
        printf("Введите элемент массива: ");
        ++alen;
    }
    return alen;
}

void print_arr(arr a, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
        printf("%d ", a[i]);
    return;
}

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
    size_t alen = 0;
    bool full_arr_flag = 0;

    alen = scan_arr(a);

    if (!alen)
    {
        printf("Введите хотя бы один элемент!\n");
        return EMPTY_ARRAY_ERROR;
    }

    if (alen > NMAX)
    {
        alen = NMAX;
        full_arr_flag = 1;
    }

    insertion_sort(a, alen);

    printf("Отсортированный массив: ");
    print_arr(a, alen);
    printf("\n");

    if (full_arr_flag)
        return FULL_ARRAY_ERROR;

    return EVERYTHING_OK;
}
