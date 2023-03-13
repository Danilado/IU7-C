#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define NO_POS_ELEMENTS_ERROR 2

typedef int arr[NMAX];

size_t scan_len(void)
{
    size_t alen;
    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
        return 0;

    return alen;
}

size_t scan_arr(arr a, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
    {
        printf("Введите элемент массива: ");
        if (scanf("%d", &a[i]) != 1)
            return i;
    }
    return alen;
}

double pos_geom_mean(arr a, size_t alen)
{
    size_t pos_count = 0;
    double prod = 1;

    for (size_t i = 0; i < alen; ++i)
        if (a[i] > 0)
        {
            ++pos_count;
            prod *= a[i];
        }

    if (!pos_count)
        return 0;

    return pow(prod, (double)1 / pos_count);
}

int main(void)
{
    arr a;
    size_t alen = 0;
    double geom_mean;

    alen = scan_len();
    if (!alen)
    {
        puts("Ошибка ввода");
        return INPUT_ERROR;
    }

    if (scan_arr(a, alen) != alen)
    {
        puts("Ошибка ввода");
        return INPUT_ERROR;
    }

    geom_mean = pos_geom_mean(a, alen);
    if (!geom_mean)
    {
        printf("В массиве нет положительных элементов!\n");
        return NO_POS_ELEMENTS_ERROR;
    }

    printf("Среднее геометрическое положительных элементов массива: ");
    printf("%.6lf\n", geom_mean);

    return EVERYTHING_OK;
}
