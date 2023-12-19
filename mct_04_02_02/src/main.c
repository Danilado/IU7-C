#include "my_int_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    node_t list = NULL;
    long len = 0;
    int rc = 0;

#ifdef VERBOSE
    printf("list_len: ");
#endif

    if (scanf("%ld", &len) != 1)
        return 1;

    if (!len || len < 0)
        return 1;

    for (size_t i = 0; i < (size_t)len; ++i)
    {
        int tmp;
#ifdef VERBOSE
        printf("element: ");
#endif
        if (scanf("%d", &tmp) != 1)
        {
            rc = 1;
            goto clear;
        }
        if (list_push(&list, tmp))
        {
            rc = 1;
            goto clear;
        }
    }

    int running = 1;
    while (running)
    {

#ifdef VERBOSE
        printf("0: exit\n");
        printf("1: push\n");
        printf("2: remove 3rd min\n");
        printf("3: swap 2nd with max\n");
        printf("4: print\n");
        printf("> ");
#endif

        int tmp;
        if (scanf("%d", &tmp) != 1)
            continue;

        if (tmp == 0)
        {
            running = 0;
            continue;
        }

        if (tmp == 1)
        {
            int tmp;

#ifdef VERBOSE
            printf("element: ");
#endif
            if (scanf("%d", &tmp) != 1)
            {

#ifdef VERBOSE
                puts("bad input");
#endif
                continue;
            }
            if (list_push(&list, tmp))
            {
                rc = 1;
                goto clear;
            }
            continue;
        }

        if (tmp == 2)
        {
            node_t tmp = list_get_3rd_min(list);
            if (!tmp)
            {
#ifdef VERBOSE
                puts("not enough elements\n");
#endif
                continue;
            }

            list_remove(&list, tmp);
            continue;
        }

        if (tmp == 3)
        {
            if (list_swap_max_2nd(&list))
            {
#ifdef VERBOSE
                puts("not enough elements\n");
#endif
                continue;
            }
        }

        if (tmp == 4)
        {
            list_print(list);
            continue;
        }
    }

clear:
    list_clear(&list);
    return rc;
}
