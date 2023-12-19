#include "my_dynamic_arr.h"

int dyn_arr_init(size_t el_size, size_t el_count, my_dyn_arr_t *dst)
{
    void *ptr = calloc(el_count, el_size);
    if (ptr == NULL)
        return NOT_ENOUGH_MEMORY;

    dst->pb = ptr;
    dst->pe = (char *)ptr + el_size * el_count;
    dst->el_size = el_size;

    return EXIT_SUCCESS;
}

void dyn_arr_destroy(my_dyn_arr_t *arr)
{
    free(arr->pb);
    arr->pb = NULL;
    arr->pe = NULL;
    arr->el_size = 0;
}
