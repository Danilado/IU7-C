#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define NO_ARMSTRONG_NUMBERS_ERROR 2

typedef int arr_t[NMAX];

size_t arr_scan(arr_t a, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
        if (scanf("%d", &a[i]) != 1)
            return i;
    return alen;
}

void print_arr(arr_t a, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
        printf("%d ", a[i]);
    return;
}

int count_digits(int n)
{
    if (n == 0)
        return 1;

    int digit_count = 0;
    while (n != 0)
    {
        ++digit_count;
        n /= 10;
    }

    return digit_count;
}

bool is_armstrong(int n)
{
    // Числа армстронга натуральные
    if (n <= 0)
        return false;

    // clang-format off
    // Всего в 32-битном типе int помещается 31 число армстронга
    int32_t armstrongs[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        153, 370, 371, 407, 1634,
        8208, 9474, 54748, 92727,
        93084, 548834, 1741725, 
        4210818, 9800817, 9926315, 
        24678050, 24678051, 88593477,
        146511208, 472335975, 534494836,
        912985153
    };

    const size_t alen = sizeof(armstrongs) / sizeof(armstrongs[0]);
    // clang-format on

    for (size_t i = 0; i < alen; ++i)
        if (n == armstrongs[i])
            return true;

    return false;
}

size_t copy_armstrong(int src[], int dst[], size_t srclen)
{
    size_t dstlen = 0;
    for (size_t i = 0; i < srclen; ++i)
    {
        if (src[i] > 0 && is_armstrong(src[i]))
        {
            dst[dstlen] = src[i];
            ++dstlen;
        }
    }
    return dstlen;
}

int main(void)
{
    arr_t a, out;
    size_t alen = 0, olen = 0;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || !alen || alen > 10)
        return INPUT_ERROR;

    if (arr_scan(a, alen) != alen)
    {
        puts("Ошибка ввода");
        return INPUT_ERROR;
    }

    olen = copy_armstrong(a, out, alen);

    if (!olen)
    {
        printf("В массиве нет чисел Армстронга\n");
        return NO_ARMSTRONG_NUMBERS_ERROR;
    }

    printf("Числа Армстронга: ");
    print_arr(out, olen);
    printf("\n");

    return EVERYTHING_OK;
}
