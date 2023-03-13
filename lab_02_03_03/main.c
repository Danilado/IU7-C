#include <inttypes.h>
#include <stdio.h>

#define NMAX 20

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

void print_arr(arr a, size_t alen)
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

size_t copy_rev_pos(arr a, arr b, size_t alen)
{
    size_t blen = 0;
    for (size_t i = 0; i < alen; ++i)
    {
        b[blen] = a[i];
        ++blen;
        if (a[i] > 0)
        {
            b[blen] = reverse_num(a[i]);
            ++blen;
        }
    }
    return blen;
}

int main(void)
{
    arr a, o;
    size_t alen = 0, olen = 0;

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

    olen = copy_rev_pos(a, o, alen);

    printf("Новый массив: ");
    print_arr(o, olen);
    printf("\n");

    return EVERYTHING_OK;
}
