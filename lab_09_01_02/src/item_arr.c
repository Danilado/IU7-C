#include "item_arr.h"

struct item_arr_type_t
{
    item_t *base;
    size_t el_count;
    size_t capacity;
};

item_arr_t item_arr_create(void)
{
    item_arr_t res = calloc(1, sizeof(struct item_arr_type_t));
    if (!res)
        return NULL;

    res->base = NULL;
    res->capacity = 0;
    res->el_count = 0;

    return res;
}

void item_arr_destroy(item_arr_t arr)
{
    for (size_t i = 0; i < arr->el_count; ++i)
        item_destroy(arr->base[i]);
    free(arr->base);
    free(arr);
}

int item_arr_expand(item_arr_t arr)
{
    size_t newcount = (size_t)(arr->capacity * 1.15) + 1;

    void *tmp = realloc(arr->base, sizeof(item_t) * newcount);

    if (!tmp)
        return NO_MEMORY;

    arr->base = tmp;
    arr->capacity = newcount;

    return EXIT_SUCCESS;
}

int item_arr_minimize(item_arr_t arr)
{
    if (arr->capacity == arr->el_count)
        return EXIT_SUCCESS;

    void *tmp = realloc(arr->base, sizeof(item_t) * arr->el_count);
    if (!tmp)
        return BAD_BASE_REALLOC;

    arr->base = tmp;
    arr->capacity = arr->el_count;

    return EXIT_SUCCESS;
}

int item_arr_push(item_arr_t arr, item_t item)
{
    if (arr->el_count == arr->capacity)
    {
        int rc = item_arr_expand(arr);
        if (rc)
            return rc;
    }

    arr->base[arr->el_count] = item;
    ++arr->el_count;

    return EXIT_SUCCESS;
}

int item_arr_scanf(item_arr_t dst, FILE *stream)
{
    while (!feof(stream))
    {
        item_t tmp = item_create();
        int rc;

        rc = item_scanf(tmp, stream);
        if (rc)
        {
            item_destroy(tmp);

            if (rc == NO_NAME && dst->el_count != 0 && feof(stream))
                break;
            return rc;
        }

        rc = item_arr_push(dst, tmp);
        if (rc)
        {
            item_destroy(tmp);
            return rc;
        }
    }

    return EXIT_SUCCESS;
}

size_t pref_items_print(const item_arr_t arr, char *prefix)
{
    size_t printed_count = 0;

    for (size_t i = 0; i < arr->el_count; ++i)
        if (strlen(prefix) == 0 ||
            strncmp(item_get_name(arr->base[i]), prefix, strlen(prefix)) == 0)
        {
            item_print(arr->base[i]);
            ++printed_count;
        }

    return printed_count;
}

int density_comparator(const void *vi1, const void *vi2)
{
    const item_t *i1 = (void *)vi1;
    const item_t *i2 = (void *)vi2;
    double d1, d2;
    d1 = item_get_density(*i1);
    d2 = item_get_density(*i2);

    if (fabs(d2 - d1) < EPS)
        return 0;

    if (d2 - d1 > 0)
        return -1;

    return 1;
}

void sort_by_density(item_arr_t arr)
{
    qsort(arr->base, arr->el_count, sizeof(item_t), density_comparator);
}

size_t item_arr_get_length(item_arr_t arr)
{
    return arr->el_count;
}

size_t item_arr_get_capacity(item_arr_t arr)
{
    return arr->capacity;
}

item_t item_arr_get_by_index(item_arr_t arr, size_t index)
{
    if (index >= arr->el_count)
        return NULL;
    return arr->base[index];
}
