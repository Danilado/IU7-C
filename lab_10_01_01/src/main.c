#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef POSIX_C_SOURCE
#define POSIX_C_SOURCE 200809L
#endif

#include "item.h"
#include "my_list.h"
#include <stdlib.h>

enum errors
{
    BAD_MODE = 1,
    BAD_FILENAME,
    PARSING_ERRORS,
    NOTHING_TO_PRINT,
};

int item_list_fscanf(node_t **head, FILE *stream)
{
    while (!feof(stream))
    {
        item_t tmp = item_create();
        int rc;

        rc = item_scanf(tmp, stream);
        if (rc)
        {
            item_destroy(tmp);

            if (rc == NO_NAME && list_get_length(*head) != 0 && feof(stream))
                break;
            return rc;
        }

        rc = list_push_value(head, tmp);
        if (rc)
        {
            item_destroy(tmp);
            return rc;
        }
    }

    return EXIT_SUCCESS;
}

void item_in_list_destroy(node_t *node)
{
    item_t item = node->data;
    item_destroy(item);
}

void item_list_destroy(node_t **head)
{
    list_apply(*head, item_in_list_destroy);
    list_destroy(head);
}

void item_in_list_printf(node_t *node)
{
    item_t item = node->data;
    item_print(item);
}

int main(int argc, char **argv)
{
    int rc;

    if (argc != 2)
        return BAD_MODE;

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
        return BAD_FILENAME * 10;

    node_t **list = calloc(1, sizeof(node_t *));

    rc = item_list_fscanf(list, input_file);
    fclose(input_file);
    if (rc)
    {
        item_list_destroy(list);
        return PARSING_ERRORS * 10 + rc;
    }

    *list = sort(*list, density_comparator);
    list_apply(*list, item_in_list_printf);

    item_list_destroy(list);
    return EXIT_SUCCESS;
}
