#include "array.h"

void arr_print(arr_t arr, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}
