#include <inttypes.h>
#include <stdio.h>

#define NMAX 20

#define EVERYTHING_OK 0
#define INPUT_ERROR 1

typedef int arr[NMAX];

int reverse(int n)
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

size_t copy_rev_pos(arr a, arr b, size_t alen)
{
    size_t blen = 0;
    for (size_t i = 0; i < alen; ++i)
    {
        b[blen] = a[i];
        ++blen;
        if (a[i] > 0)
        {
            b[blen] = reverse(a[i]);
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

    olen = copy_rev_pos(a, o, alen);

    printf("Новый массив: ");
    for (size_t i = 0; i < olen; ++i)
        printf("%d ", o[i]);
    printf("\n");

    return EVERYTHING_OK;
}
