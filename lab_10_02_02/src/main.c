#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef POSIX_C_SOURCE
#define POSIX_C_SOURCE 200809L
#endif

#include "my_list.h"
#include "polynome_list.h"
#include <stdlib.h>

enum errors
{
    BAD_MODE = 1,
    PARSING_ERRORS,
    NOTHING_TO_PRINT,
};

enum modes
{
    UNKNOWN_MODE,
    VAL,
    DDX,
    SUM,
    DVD,
};

int read_mode(void)
{
    size_t buflen = 3 + 1;
    char *buf = calloc(buflen, sizeof(char));

    ssize_t rc = getline(&buf, &buflen, stdin);
    if (rc < 0)
    {
        free(buf);
        return UNKNOWN_MODE;
    }

    // Если считано только \n
    if (rc == 1)
    {
        free(buf);
        return UNKNOWN_MODE;
    }

    buf[strcspn(buf, "\n")] = '\0';

    if (strncmp(buf, "val", buflen) == 0)
    {
        free(buf);
        return VAL;
    }
    if (strncmp(buf, "ddx", buflen) == 0)
    {
        free(buf);
        return DDX;
    }
    if (strncmp(buf, "sum", buflen) == 0)
    {
        free(buf);
        return SUM;
    }
    if (strncmp(buf, "dvd", buflen) == 0)
    {
        free(buf);
        return DVD;
    }
    free(buf);
    return UNKNOWN_MODE;
}

int main(void)
{
    int rc;
    int mode = read_mode();
    if (!mode)
        return BAD_MODE;

    if (mode == VAL)
    {
        node_t **poly_list = calloc(1, sizeof(node_t *));
        rc = poly_list_scanf(poly_list);

        if (rc)
        {
            list_apply(*poly_list, pow_destroy);
            list_destroy(poly_list);
            return rc;
        }

        int tmp;
        if (scanf("%d", &tmp) != 1)
        {
            list_apply(*poly_list, pow_destroy);
            list_destroy(poly_list);
            return PARSING_ERRORS;
        }

        int res = poly_list_get_value(*poly_list, tmp);
        printf("%d\n", res);
        list_apply(*poly_list, pow_destroy);
        list_destroy(poly_list);
    }

    if (mode == DDX)
    {
        node_t **poly_list = calloc(1, sizeof(node_t *));
        node_t *ddx_list;
        rc = poly_list_scanf(poly_list);
        if (rc)
        {
            list_apply(*poly_list, pow_destroy);
            list_destroy(poly_list);
            return rc;
        }

        ddx_list = poly_list_derivative(*poly_list);
        poly_list_printf(ddx_list);

        list_apply(*poly_list, pow_destroy);
        list_apply(ddx_list, pow_destroy);
        list_destroy(poly_list);
        list_clear(&ddx_list);
    }

    if (mode == SUM)
    {
        node_t **poly_list1 = calloc(1, sizeof(node_t *));
        node_t **poly_list2 = calloc(1, sizeof(node_t *));
        node_t *sum_list;

        rc = poly_list_scanf(poly_list1);
        if (rc)
        {
            list_apply(*poly_list1, pow_destroy);
            list_destroy(poly_list1);
            list_destroy(poly_list2);
            return rc;
        }
        rc = poly_list_scanf(poly_list2);
        if (rc)
        {
            list_apply(*poly_list1, pow_destroy);
            list_destroy(poly_list1);
            list_apply(*poly_list2, pow_destroy);
            list_destroy(poly_list2);
            return rc;
        }

        sum_list = poly_list_sum(*poly_list1, *poly_list2);
        poly_list_printf(sum_list);

        list_apply(*poly_list1, pow_destroy);
        list_destroy(poly_list1);
        list_apply(*poly_list2, pow_destroy);
        list_destroy(poly_list2);
        list_apply(sum_list, pow_destroy);
        list_clear(&sum_list);
    }

    if (mode == DVD)
    {
        node_t **poly_list = calloc(1, sizeof(node_t *));
        node_t **odd = calloc(1, sizeof(node_t *));
        node_t **even = calloc(1, sizeof(node_t *));
        rc = poly_list_scanf(poly_list);

        if (rc)
        {
            list_apply(*poly_list, pow_destroy);
            list_destroy(poly_list);
            list_destroy(even);
            list_destroy(odd);
            return rc;
        }

        rc = poly_list_split(*poly_list, odd, even);
        if (!rc)
        {
            poly_list_printf(*even);
            poly_list_printf(*odd);
        }
        list_apply(*poly_list, pow_destroy);
        list_destroy(poly_list);
        list_apply(*odd, pow_destroy);
        list_destroy(odd);
        list_apply(*even, pow_destroy);
        list_destroy(even);

        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}
