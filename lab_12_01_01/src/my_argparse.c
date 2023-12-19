#include "my_argparse.h"

int my_argparse(int argc, char **argv, args_t *dst)
{
    if (argc < MIN_ARGS)
        return NOT_ENOUGH_ARGS;

    if (argc > MAX_ARGS)
        return TOO_MUCH_ARGS;

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
        return INVALID_INPUT_FILE;

    FILE *fout = fopen(argv[2], "w");
    if (fout == NULL)
    {
        fclose(fin);
        return INVALID_OUTPUT_FILE;
    }

    dst->file_in = fin;
    dst->file_out = fout;
    dst->filter = false;

    if (argc == MAX_ARGS)
    {
        if (strcmp(argv[3], "f") != 0)
        {
            fclose(fin);
            fclose(fout);
            return INVALID_3RD_ARG;
        }

        dst->filter = true;
    }

    return EXIT_SUCCESS;
}
