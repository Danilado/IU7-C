#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1

typedef int arr_t[NMAX];

size_t scan_arr(int *pb, int *pe)
{
    for (int *pcur = pb; pcur < pe; ++pcur)
    {
        if (scanf("%d", pcur) != 1)
            return pcur - pb;
    }
    return pe - pb;
}

int arr_prod(int *pb, int *pe)
{
    int prod = 1;

    for (int *pcur = pb; pcur < pe; ++pcur)
        prod *= *pcur;

    return prod;
}

// считает сумму произведений частей массива
int my_prods(int *pb, int *pe)
{
    int res = 0;
    for (int *pcur = pb; pcur < pe; ++pcur)
    {
        res += arr_prod(pb, pcur + 1);
        if (*pcur <= 0)
            break;
    }

    return res;
}

int main(void)
{
    arr_t a;
    int *pa = a;
    int res = 0;
    size_t alen = 0;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
        return INPUT_ERROR;

    printf("Введите массив: ");
    if (scan_arr(pa, pa + alen) != alen)
    {
        printf("Ошибка ввода\n");
        return INPUT_ERROR;
    }

    res = my_prods(pa, pa + alen);

    printf("Полученное значение: %d\n", res);

    return EVERYTHING_OK;
}
