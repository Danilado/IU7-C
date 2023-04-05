#include "array.h"

void arr_shift_left(arr_t arr, size_t alen, int amount)
{
    amount %= alen;

    for (int i = 0; i < amount; ++i)
    {
        int tmp = arr[0];
        for (size_t j = 0; j < alen - 1; ++j)
            arr[j] = arr[j + 1];
        arr[alen - 1] = tmp;
    }
}
