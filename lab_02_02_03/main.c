#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define NO_ARMSTRONG_NUMBERS_ERROR 2

typedef int arr[NMAX];

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
    if (n == 0)
        return false;

    int n_copy = n, sum = 0, digc = count_digits(n);

    while (n_copy != 0)
    {
        sum += (int)pow((double)(n_copy % 10), (double)digc);
        n_copy /= 10;
    }

    return sum == n;
}

int filter_armstrong(int a[], int b[], size_t alen)
{
    size_t blen = 0;
    for (size_t i = 0; i < alen; ++i)
    {
        if (a[i] > 0 && is_armstrong(a[i]))
        {
            b[blen] = a[i];
            ++blen;
        }
    }
    return blen;
}

int main(void)
{
    arr a, o;
    size_t alen = 0, olen = 0;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen <= 0 || alen > 10)
    {
        printf("Ошибка ввода\n");
        return INPUT_ERROR;
    }

    for (size_t i = 0; i < alen; ++i)
    {
        printf("Введите элемент массива: ");
        if (scanf("%d", &a[i]) != 1)
        {
            printf("Ошибка ввода\n");
            return INPUT_ERROR;
        }
    }

    olen = filter_armstrong(a, o, alen);

    if (!olen)
    {
        printf("В массиве нет чисел Армстронга\n");
        return NO_ARMSTRONG_NUMBERS_ERROR;
    }

    printf("Числа Армстронга: ");
    for (size_t i = 0; i < olen; ++i)
        printf("%d ", o[i]);
    printf("\n");

    return 0;
}
