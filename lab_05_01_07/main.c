#include "tuple.h"
#include <stdio.h>
#include <stdlib.h>

#define NO_INPUT -1

int process(FILE *f, unsigned *dst)
{
    *dst = 0;

    tuple last_els;
    init_tuple(&last_els);

    int tmp;
    while (fscanf(f, "%d", &tmp) == 1)
    {
        push_ino_tuple(&last_els, tmp);
        if (last_els.filled_els == 3)
            if (last_els.cur > last_els.prev && last_els.cur > last_els.next)
                ++(*dst);
    }

    if (last_els.filled_els < 3)
        return NO_INPUT - last_els.filled_els;

    return 0;
}

int main(void)
{
    unsigned ans;
    int rc = process(stdin, &ans);

    if (rc)
        return rc;

    fprintf(stdout, "%u\n", ans);
    return EXIT_SUCCESS;
}
