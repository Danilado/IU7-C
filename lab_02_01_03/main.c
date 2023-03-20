#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define NO_POS_ELEMENTS_ERROR 2

typedef int arr_t[NMAX];

size_t arr_scan(arr_t a, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
    {
        if (scanf("%d", &a[i]) != 1)
            return i;
    }
    return alen;
}

double pos_geom_mean(arr_t a, size_t alen)
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

    return pow(prod, 1.0 / pos_count);
}

int main(void)
{
    arr_t a;
    size_t alen = 0;
    double geom_mean;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
        return INPUT_ERROR;

    printf("Введите массив: ");
    if (arr_scan(a, alen) != alen)
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
