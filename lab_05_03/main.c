#include "int32_file.h"
#include "my_args.h"

int main(int argc, char **argv)
{
    args_s args;
    int rc;

    rc = parse_args(argc, argv, &args);

    if (rc)
        return rc;

    // clang-format off
    switch (args.mode)
    {
        case CREATE_MODE:
            rc = (create_file(&args) == args.number ? 0 : WRITE_ERROR);
            break;
        case PRINT_MODE:
            rc = print_file(&args);
            break;
        case SORT_MODE:
            rc = sort_file(&args);
            break;
        default:
            break;
    }
    // clang-format on

    if (rc)
        return rc;

    return EXIT_SUCCESS;
}
