#include "my_argparse.h"

int my_argparse(int argc, char **argv, args_t *args)
{
    if (argc < 2)
        return NO_FILENAME_ERROR;

    if (argc > 3)
        return TOO_MANY_ARGS;

    args->filename = argv[1];

    if (argc == 2)
        args->mode = SORT_N_PRINT;
    else
    {
        if (strcmp(argv[2], PRINT_ALL_PREFIX) == 0)
            args->mode = PRINT_ALL;
        else
        {
            args->mode = CHECK_PREFIX;
            args->prefix = argv[2];
        }
    }

    return 0;
}
