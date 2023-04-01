#include "./arrays.h"

void arr_fill(arr_t dst, size_t num)
{
    for (size_t i = 0; i < num; ++i)
        dst[i] = i;
}
