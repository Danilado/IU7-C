#include "my_argparse.h"

int my_argparse(int argc, char **argv, args_s *args)
{
    if (argc < 2)
        return NO_MODE;

    if (strcmp(argv[1], SORT_MODE) == 0)
    {
        args->mode = SORT_MODE_CODE;

        if (argc - 2 < SORT_MODE_ARGC)
            return NOT_ENOUGH_ARGS;
        else if (argc - 2 > SORT_MODE_ARGC)
            return TOO_MUCH_ARGS;

        args->arg1 = argv[2];
        args->arg2 = argv[3];
    }
    else if (strcmp(argv[1], PRINT_MODE) == 0)
    {
        args->mode = PRINT_MODE_CODE;

        if (argc - 2 < PRINT_MODE_ARGC)
            return NOT_ENOUGH_ARGS;
        else if (argc - 2 > PRINT_MODE_ARGC)
            return TOO_MUCH_ARGS;

        args->arg1 = argv[2];
        args->arg2 = argv[3];
    }
    else if (strcmp(argv[1], ADD_MODE) == 0)
    {
        args->mode = ADD_MODE_CODE;

        if (argc - 2 < ADD_MODE_ARGC)
            return NOT_ENOUGH_ARGS;
        else if (argc - 2 > ADD_MODE_ARGC)
            return TOO_MUCH_ARGS;

        args->arg1 = argv[2];
    }
    else
        return BAD_MODE;

    return 0;
}
