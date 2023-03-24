#include <inttypes.h>
#include <stdio.h>

#define NMAX 20

#define EVERYTHING_OK 0
#define INPUT_ERROR 1

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

int reverse_num(int n)
{
    int r = 0;
    while (n != 0)
    {
        r *= 10;
        r += n % 10;
        n /= 10;
    }
    return r;
}

size_t copy_rev_pos(arr_t src, arr_t dst, size_t srclen)
{
    size_t dstlen = 0;
    for (size_t i = 0; i < srclen; ++i)
    {
        dst[dstlen] = src[i];
        ++dstlen;
        if (src[i] > 0)
        {
            dst[dstlen] = reverse_num(src[i]);
            ++dstlen;
        }
    }
    return dstlen;
}

int main(void)
{
    arr_t a, o;
    size_t alen = 0, olen = 0;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || !alen || alen > 10)
        return INPUT_ERROR;

    if (arr_scan(a, alen) != alen)
    {
        puts("Ошибка ввода");
        return INPUT_ERROR;
    }

    olen = copy_rev_pos(a, o, alen);

    printf("Новый массив: ");
    print_arr(o, olen);
    printf("\n");

    return EVERYTHING_OK;
}
