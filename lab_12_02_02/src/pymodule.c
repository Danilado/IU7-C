#include "pymodule.h"

int arr_fib_fill(int *dst, size_t amount)
{
    int fibnumbers_in_int[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144,
    233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368,
    75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578,
    5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155,
    165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903};

    size_t fibcount = sizeof(fibnumbers_in_int) / sizeof(fibnumbers_in_int[0]);

    if (amount > fibcount)
        return TOO_MUCH;

    for (size_t i = 0; i < amount; ++i)
        dst[i] = fibnumbers_in_int[i];

    return 0;
}

static bool number_in_arr(int *arr, size_t el_count, int num)
{
    for (size_t i = 0; i < el_count; ++i)
        if (arr[i] == num)
            return true;

    return false;
}

size_t arr_unique(int *src, size_t el_count, int *dst)
{
    size_t newsize = 0;
    for (size_t i = 0; i < el_count; ++i)
        if (!number_in_arr(dst, newsize, src[i]))
        {
            dst[newsize] = src[i];
            ++newsize;
        }

    return newsize;
}
