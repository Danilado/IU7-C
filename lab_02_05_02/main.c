#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1

typedef int arr[NMAX];

size_t scan_len(void)
{
    size_t alen;
    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
        return 0;

    return alen;
}

size_t scan_arr(int *pb, int *pe)
{
    for (int *pcur = pb; pcur < pe; ++pcur)
    {
        printf("Введите элемент массива: ");
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

int prod_sum(int *pb, int *pe)
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
    arr a;
    int *pa = a;
    int res = 0;
    size_t alen = 0;

    alen = scan_len();
    if (!alen)
    {
        puts("Ошибка ввода");
        return INPUT_ERROR;
    }

    if (scan_arr(pa, pa + alen) != alen)
    {
        puts("Ошибка ввода");
        return INPUT_ERROR;
    }

    res = prod_sum(pa, pa + alen);

    printf("Полученное значение: %d\n", res);

    return EVERYTHING_OK;
}
