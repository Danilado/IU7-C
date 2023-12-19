#include "item.h"
#include "my_argparse.h"
#include <stdlib.h>

enum errors
{
    BAD_ARGS = 1,
    BAD_FILENAME,
    PARSING_ERRORS,
    NOTHING_TO_PRINT,
};

int main(int argc, char **argv)
{
    args_t args;
    int rc;

    rc = my_argparse(argc, argv, &args);
    if (rc)
        return BAD_ARGS * 10 + rc;

    FILE *input_file = fopen(args.filename, "r");
    if (input_file == NULL)
        return BAD_FILENAME * 10;

    item_arr_t items;
    size_t items_len;

    rc = item_arr_scan(items, &items_len, input_file);
    if (rc)
    {
        fclose(input_file);
        return PARSING_ERRORS * 10 + rc;
    }

    // clang-format off

    switch (args.mode)
    {
        case PRINT_ALL:
            pref_items_print(items, items_len, "");
            break;
        case CHECK_PREFIX:
            {
                size_t printed_count; 
                printed_count = pref_items_print(items, items_len, args.prefix);
                if (!printed_count)
                    return NOTHING_TO_PRINT * 10;
            }
            break;
        case SORT_N_PRINT:
            sort_by_density(items, items_len);
            pref_items_print(items, items_len, "");
            break;
    }

    // clang-format on

    fclose(input_file);
    return EXIT_SUCCESS;
}
