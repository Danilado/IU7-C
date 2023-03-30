#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NMAX 1024
#define EPS 1e-8

#define NUM_INPUT_ERROR 1
#define LEN_INPUT_ERROR 2
#define EL_INPUT_ERROR 3
#define NOTHING_TO_OUTPUT_ERROR 4

typedef int arr_t[NMAX];
typedef int out_arr_t[2 * NMAX];

bool is_full_square(int n)
{
    return (sqrt(n) - (int)sqrt(n)) <= EPS;
}

bool is_two_digit(int n)
{
    n = abs(n);
    return n < 99 && n > 9;
}

size_t arr_scan(arr_t a, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
        if (scanf("%d", &a[i]) != 1)
            return i;
    return alen;
}

void arr_print(int *ps, int *pe)
{
    for (int *pcur = ps; pcur < pe; ++pcur)
        printf("%d ", *pcur);
    printf("\n");
    return;
}

/*
Функция-фильтр принимающая в себя исходный массив - src
и выходной - dst
а также длину исходного массива - srclen формата size_t
возвращает длину выходного массива и изменяет
выходной массив в процессе выполнения оставляя
в нём только полные квадраты из исходного
MEMORY OVERLAP - UNDEFINED BEHAVIOUR
*/
size_t filter_squares(out_arr_t dst, arr_t src, size_t srclen)
{
    size_t dstlen = 0;
    for (size_t i = 0; i < srclen; ++i)
        if (src[i] >= 0 && is_full_square(src[i]))
        {
            dst[dstlen] = src[i];
            ++dstlen;
        }

    return dstlen;
}

/*
Функция принимающая в себя исходный массив - src
и выходной - dst
а также длину исходного массива - srclen формата size_t
возвращает длину выходного массива и вносит в выходной
массив копию входного с добавление числа переданного
в качестве 4 аргумента после каждого двузначного числа
MEMORY OVERLAP - UNDEFINED BEHAVIOUR
*/
size_t add_nums(out_arr_t dst, arr_t src, size_t srclen, int num)
{
    size_t dstlen = 0;
    for (size_t i = 0; i < srclen; ++i)
    {
        if (is_two_digit(src[i]))
        {
            dst[dstlen] = src[i];
            dst[dstlen + 1] = num;
            dstlen += 2;
        }
        else
        {
            dst[dstlen] = src[i];
            ++dstlen;
        }
    }

    return dstlen;
}

int main(void)
{
    size_t alen;
    arr_t a;
    int num;

    printf("Введите число n для вставки: ");
    if (scanf("%d", &num) != 1)
        return NUM_INPUT_ERROR;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > NMAX)
        return LEN_INPUT_ERROR;

    printf("Введите массив: ");
    if (arr_scan(a, alen) != alen)
        return EL_INPUT_ERROR;

    size_t blen;
    out_arr_t b;

    blen = filter_squares(b, a, alen);

    if (!blen)
        return NOTHING_TO_OUTPUT_ERROR;

    printf("\nПолные квадраты в массиве: ");
    arr_print(b, b + blen);

    // здесь пустого выходного массива быть не может,
    // потому что тогда мы бы вышли на 120-й строке
    blen = add_nums(b, a, alen, num);

    printf("\nДополненный массив: ");
    arr_print(b, b + blen);

    return EXIT_SUCCESS;
}
