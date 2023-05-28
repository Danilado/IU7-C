#include "my_args.h"

int parse_args(int argc, char **argv, args_s *args)
{
    if (strlen(argv[1]) != 1)
        return BAD_ARG_ORDER;

    // clang-format off
    switch (argv[1][0])
    {
        case CREATE_MODE:
            if (argc < 4)
                return NOT_ENOUGH_ARGS;
            args->mode = CREATE_MODE;
            args->filename = argv[2];
            if (sscanf(argv[3], "%d", &args->number) != 1 || args->number <= 0)
                return BAD_NUMBER;
            break;
        case PRINT_MODE:
            if (argc > 3)
                return TOO_MUCH_ARGS;
            args->mode = PRINT_MODE;
            args->filename = argv[2];
            args->number = 0;
            break;
        case SORT_MODE:
            if (argc > 3)
                return TOO_MUCH_ARGS;
            args->mode = SORT_MODE;
            args->filename = argv[2];
            args->number = 0;
            break;
        default:
            return BAD_MODE;
    }
    // clang-format on

    return 0;
}
