#include "file.h"
#include <stdio.h>
#include <stdlib.h>

#define TARGET_ARGS 2

#define BAD_INPUT_FILE 3
#define BAD_ARGC 4

int main(int argc, char **argv)
{
    if (argc != TARGET_ARGS)
        return BAD_ARGC;

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
        return BAD_INPUT_FILE;

    double variance;
    int rc;
    rc = variance_from_file(input_file, &variance);

    fclose(input_file);

    if (rc)
        return rc;

    fprintf(stdout, "%.6lf\n", variance);

    return EXIT_SUCCESS;
}
