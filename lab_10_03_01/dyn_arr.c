#include "dyn_arr.h"

struct dyn_arr
{
    void **base;
    size_t el_count;
    size_t capacity;
};

dyn_arr_t dyn_arr_create(void)
{
    dyn_arr_t res = calloc(1, sizeof(struct dyn_arr));
    if (!res)
        return NULL;

    res->base = NULL;
    res->capacity = 0;
    res->el_count = 0;

    return res;
}

void dyn_arr_destroy(dyn_arr_t arr)
{
    free(arr->base);
    free(arr);
}

int dyn_arr_expand(dyn_arr_t arr)
{
    size_t newcount = (size_t)(arr->capacity * 1.15) + 1;

    void *tmp = realloc(arr->base, sizeof(void *) * newcount);

    if (!tmp)
        return NO_MEMORY;

    arr->base = tmp;
    arr->capacity = newcount;

    return EXIT_SUCCESS;
}

int dyn_arr_minimize(dyn_arr_t arr)
{
    if (arr->capacity == arr->el_count)
        return EXIT_SUCCESS;

    void *tmp = realloc(arr->base, sizeof(void *) * arr->el_count);
    if (!tmp)
        return BAD_BASE_REALLOC;

    arr->base = tmp;
    arr->capacity = arr->el_count;

    return EXIT_SUCCESS;
}

int dyn_arr_push(dyn_arr_t arr, void *item)
{
    if (arr->el_count == arr->capacity)
    {
        int rc = dyn_arr_expand(arr);
        if (rc)
            return rc;
    }

    arr->base[arr->el_count] = item;
    ++arr->el_count;

    return EXIT_SUCCESS;
}

size_t dyn_arr_get_length(dyn_arr_t arr)
{
    return arr->el_count;
}

size_t dyn_arr_get_capacity(dyn_arr_t arr)
{
    return arr->capacity;
}

void *dyn_arr_get_by_index(dyn_arr_t arr, size_t index)
{
    if (index >= arr->el_count)
        return NULL;
    return arr->base[index];
}

void dyn_arr_remove_by_index(dyn_arr_t arr, size_t index)
{
    if (index >= arr->el_count)
        return;

    memmove(&arr->base[index], &arr->base[index + 1],
    sizeof(void *) * (arr->el_count - index - 1));

    // for (size_t i = index; i + 1 < arr->el_count; ++i)
    //     arr->base[i] = arr->base[i + 1];

    --arr->el_count;
}

void dyn_arr_set_by_index(dyn_arr_t arr, size_t index, void *value)
{
    if (index > arr->el_count)
        return;
    if (index == arr->el_count)
    {
        dyn_arr_push(arr, value);
        return;
    }
    arr->base[index] = value;
}
