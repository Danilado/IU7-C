#include <stdio.h>
#include <stdlib.h>

#include "my_matrix.h"
#include "my_utils.h"

#define BAD_SIZE_INPUT 1;
#define BAD_POW_INPUT 2;

#define MATRIX_ERROR 10;

int main(void)
{
    int rc = 0;

    long m, n;
    long p, q;
    matrix_t a, b;

    puts("matrix a size");
    if (scanf("%ld", &m) != 1)
        return BAD_SIZE_INPUT;
    if (scanf("%ld", &n) != 1)
        return BAD_SIZE_INPUT;

    if (m <= 0 || n <= 0)
        return BAD_SIZE_INPUT;

    rc = matrix_init(&a, m, n);
    if (rc)
        return rc + MATRIX_ERROR;

    puts("matrix a");
    rc = matrix_scanf(&a);
    if (rc)
    {
        matrix_destroy(&a);
        return rc + MATRIX_ERROR;
    }

    puts("matrix b size");
    if (scanf("%ld", &p) != 1)
    {
        matrix_destroy(&a);
        return BAD_SIZE_INPUT;
    }
    if (scanf("%ld", &q) != 1)
    {
        matrix_destroy(&a);
        return BAD_SIZE_INPUT;
    }

    if (p <= 0 || q <= 0)
    {
        matrix_destroy(&a);
        return BAD_SIZE_INPUT;
    }

    rc = matrix_init(&b, p, q);
    if (rc)
    {
        matrix_destroy(&a);
        return rc + MATRIX_ERROR;
    }

    puts("matrix b");
    rc = matrix_scanf(&b);
    if (rc)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        return rc + MATRIX_ERROR;
    }

    matrix_squarify(&a);
    matrix_squarify(&b);

    rc = matrix_unify(&a, &b);
    if (rc)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        return rc + MATRIX_ERROR;
    }

    puts("ro gamma");
    long ro, gamma;
    if (scanf("%ld", &ro) != 1 || ro < 0)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        return BAD_POW_INPUT;
    }
    if (scanf("%ld", &gamma) != 1 || gamma < 0)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        return BAD_POW_INPUT;
    }

    matrix_t apowd, bpowd;

    rc = matrix_pow(&a, ro, &apowd);
    if (rc)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        return rc + MATRIX_ERROR;
    }

    rc = matrix_pow(&b, gamma, &bpowd);
    if (rc)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        matrix_destroy(&apowd);
        return rc + MATRIX_ERROR;
    }

    matrix_t result;
    rc = matrix_mul(&apowd, &bpowd, &result);
    if (rc)
    {
        matrix_destroy(&a);
        matrix_destroy(&b);
        matrix_destroy(&apowd);
        matrix_destroy(&bpowd);
        return rc + MATRIX_ERROR;
    }

    matrix_print(&result);

    matrix_destroy(&a);
    matrix_destroy(&b);
    matrix_destroy(&apowd);
    matrix_destroy(&bpowd);
    matrix_destroy(&result);
    return EXIT_SUCCESS;
}
