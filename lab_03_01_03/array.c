#include "array.h"

void arr_print(int *ps, int *pe)
{
    for (int *pcur = ps; pcur < pe; ++pcur)
        printf("%d ", *pcur);
    printf("\n");
}
