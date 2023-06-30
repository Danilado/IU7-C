#include "file.h"

int avg_from_file(FILE *f, double *dst)
{
    double sum = 0.0;
    size_t el_count = 0;

    fseek(f, 0, SEEK_SET);
    while (!feof(f))
    {
        double tmp;
        if (fscanf(f, "%lf", &tmp) != 1)
            break;

        ++el_count;
        sum += tmp;
    }

    if (!el_count)
        return NO_INPUT;
    if (el_count == 1)
        return NOT_ENOUGH_INPUT;

    *dst = sum / (double)el_count;
    return 0;
}

int variance_from_file(FILE *f, double *dst)
{
    double variance = 0;
    size_t el_count = 0;
    double avg;
    int rc;

    rc = avg_from_file(f, &avg);
    if (rc)
        return rc;

    fseek(f, 0, SEEK_SET);

    while (!feof(f))
    {
        double tmp;
        if (fscanf(f, "%lf", &tmp) != 1)
            break;

        el_count += 1;
        variance += (tmp - avg) * (tmp - avg);
    }

    *dst = variance / (double)el_count;
    return 0;
}
