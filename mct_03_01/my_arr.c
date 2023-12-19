#include "my_arr.h"

int arr_init(my_arr_t *arr, size_t el_count)
{
    void* tmp = calloc(el_count, sizeof(int));
    if(!tmp)
        return NO_MEMORY;
    
    arr->base = tmp;
    arr->capacity = el_count;
    arr->el_count = 0;

    return EXIT_SUCCESS;
}

int arr_expand(my_arr_t* arr)
{
    size_t newcount = (size_t)(arr->capacity*1.15)+1;
    void* tmp = realloc(arr->base, newcount*sizeof(int));

    if(!tmp)
        return NO_MEMORY;

    arr->base = tmp;
    arr->capacity = newcount;

    return EXIT_SUCCESS;
}

int arr_push(my_arr_t *arr, int value)
{
    if(arr->el_count >= arr->capacity)
    {
        int rc = arr_expand(arr);
        if(rc)
            return rc;
    }

    arr->base[arr->el_count] = value;
    ++arr->el_count;
    return EXIT_SUCCESS;
}

void arr_destroy(my_arr_t *arr)
{
    arr->el_count = 0;
    arr->capacity = 0;
    free(arr->base);
}

int arr_minimize(my_arr_t *arr)
{
    void* tmp = realloc(arr->base, arr->el_count * sizeof(int));
    if(!tmp)
        return NO_MEMORY;
    
    arr->base = tmp;
    arr->capacity = arr->el_count;
    return EXIT_SUCCESS;
}

int arr_remove_divisable(my_arr_t *arr, unsigned divisor)
{
    size_t newcount = 0;

    for(size_t i = 0; i < arr->el_count; ++i)
    {
        if(arr->base[i] % divisor != 0)
        {
            arr->base[newcount] = arr->base[i];
            ++newcount;
        }
    }

    arr->el_count = newcount;
    int rc = arr_minimize(arr);
    if(rc)
        return rc;

    return EXIT_SUCCESS;
}

void arr_print(my_arr_t *arr)
{
    if(arr->el_count == 0)
    {
        puts("Массив пуст");
        return;
    }

    for (size_t i = 0; i < arr->el_count; ++i)
    {
        printf("%d ", arr->base[i]);
    }
    printf("\n");
}
