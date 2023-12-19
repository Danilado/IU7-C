#include "my_arr.h"
#include <stdlib.h>
#include <stdio.h>

// Удалить из дин. массива
// числа, делящиеся на 3

int main(void)
{
    int rc;
    my_arr_t arr;
    
    rc = arr_init(&arr, 0);
    if(rc)
        return rc;

    int reading = 1;
    while(reading)
    {
        int tmp;
        if(scanf("%d", &tmp) != 1)
        {
            reading = 0;
            continue;
        }

        rc = arr_push(&arr, tmp);
        if(rc)
        {
            arr_destroy(&arr);
            return rc;
        }
    }

    puts("Вы ввели:");
    arr_print(&arr);

    rc = arr_remove_divisable(&arr, 3);
    if(arr.el_count && rc)
    {
        return rc;
    }
    
    puts("Результирующий массив:");
    arr_print(&arr);

    if(arr.el_count)
        arr_destroy(&arr);

    return EXIT_SUCCESS;
}
