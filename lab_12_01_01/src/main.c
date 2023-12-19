#include "my_argparse.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef LDL
#include "dynarr.h"
#else
#include <dlfcn.h>
#define NUM_TYPE int

typedef struct my_dyn_arr
{
    void *pb;
    void *pe;
    size_t el_size;
} my_dyn_arr_t;

typedef int (*fn_dyn_arr_init_t)(size_t, size_t, my_dyn_arr_t *);
typedef void (*fn_dyn_arr_destroy_t)(my_dyn_arr_t *);
typedef int (*fn_fill_dyn_arr_from_file_t)(my_dyn_arr_t *, FILE *);
typedef int (*fn_fprint_dyn_arr_t)(my_dyn_arr_t *, FILE *);
typedef int (*fn_swap_t)(void *, void *, size_t);
typedef void (*fn_mysort_t)(
void *, size_t, size_t, int (*)(const void *, const void *));
typedef int (*fn_int_cmp_t)(const void *, const void *);
typedef int (*fn_count_numbers_in_file_t)(FILE *, size_t *);
typedef int (*fn_key_t)(const int *, const int *, int **, int **);
#endif

enum error_classes
{
    ERROR_IN_ARGPARSE = 0,
    SCAN_ERROR = 10,
    DYN_ARR_ERROR = 20,
    PROCESSING_ERROR = 30,
    PRINT_ERROR = 40,
    LDL_ERROR = 50,
};

int main(int argc, char **argv)
{
    int rc = 0;

#ifdef LDL
    void *dynarrlib;
    dynarrlib = dlopen("./out/libdynarr.so", RTLD_NOW);
    if (!dynarrlib)
    {
        printf("Cannot open library. err: %s\n", dlerror());
        return LDL_ERROR + 1;
    }

    fn_count_numbers_in_file_t count_numbers_in_file;
    count_numbers_in_file =
    (fn_count_numbers_in_file_t)dlsym(dynarrlib, "count_numbers_in_file");
    if (!count_numbers_in_file)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_dyn_arr_init_t dyn_arr_init;
    dyn_arr_init = (fn_dyn_arr_init_t)dlsym(dynarrlib, "dyn_arr_init");
    if (!dyn_arr_init)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_fill_dyn_arr_from_file_t fill_dyn_arr_from_file;
    fill_dyn_arr_from_file =
    (fn_fill_dyn_arr_from_file_t)dlsym(dynarrlib, "fill_dyn_arr_from_file");
    if (!fill_dyn_arr_from_file)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_dyn_arr_destroy_t dyn_arr_destroy;
    dyn_arr_destroy = (fn_dyn_arr_destroy_t)dlsym(dynarrlib, "dyn_arr_destroy");
    if (!dyn_arr_destroy)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_key_t key;
    key = (fn_key_t)dlsym(dynarrlib, "key");
    if (!key)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_mysort_t mysort;
    mysort = (fn_mysort_t)dlsym(dynarrlib, "mysort");
    if (!mysort)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_fprint_dyn_arr_t fprint_dyn_arr;
    fprint_dyn_arr = (fn_fprint_dyn_arr_t)dlsym(dynarrlib, "fprint_dyn_arr");
    if (!fprint_dyn_arr)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }

    fn_int_cmp_t int_cmp;
    int_cmp = (fn_int_cmp_t)dlsym(dynarrlib, "int_cmp");
    if (!int_cmp)
    {
        printf("Error fetching function. err: %s", dlerror());
        rc = LDL_ERROR + 2;
        goto free_lib;
    }
#endif

    args_t args;
    rc = my_argparse(argc, argv, &args);
    if (rc)
#ifndef LDL
        return ERROR_IN_ARGPARSE + rc;
#else
    {
        rc = ERROR_IN_ARGPARSE + rc;
        goto free_lib;
    }
#endif

    size_t number_count;
    rc = count_numbers_in_file(args.file_in, &number_count);
    if (rc)
    {
        fclose(args.file_in);
        fclose(args.file_out);
#ifndef LDL
        return SCAN_ERROR + rc;
#else
        rc = SCAN_ERROR + rc;
        goto free_lib;
#endif
    }

    my_dyn_arr_t arr;
    rc = dyn_arr_init(sizeof(NUM_TYPE), number_count, &arr);
    if (rc)
    {
        fclose(args.file_in);
        fclose(args.file_out);
#ifndef LDL
        return DYN_ARR_ERROR + rc;
#else
        rc = DYN_ARR_ERROR + rc;
        goto free_lib;
#endif
    }

    rc = fill_dyn_arr_from_file(&arr, args.file_in);

    fclose(args.file_in);

    if (rc)
    {
        dyn_arr_destroy(&arr);
        fclose(args.file_out);
#ifndef LDL
        return PROCESSING_ERROR + rc;
#else
        rc = PROCESSING_ERROR + rc;
        goto free_lib;
#endif
    }

    if (args.filter)
    {
        my_dyn_arr_t tmp;
        tmp.el_size = arr.el_size;

        tmp.pb = calloc((char *)arr.pe - (char *)arr.pb, sizeof(char));
        tmp.pe = (char *)tmp.pb + ((char *)arr.pe - (char *)arr.pb);

        rc = key(arr.pb, arr.pe, (NUM_TYPE **)&tmp.pb, (NUM_TYPE **)&tmp.pe);
        if (rc)
        {
            dyn_arr_destroy(&arr);
            dyn_arr_destroy(&tmp);
            fclose(args.file_out);
#ifndef LDL
            return PROCESSING_ERROR + rc;
#else
            rc = PROCESSING_ERROR + rc;
            goto free_lib;
#endif
        }

        dyn_arr_destroy(&arr);
        arr = tmp;
    }

    number_count = ((char *)arr.pe - (char *)arr.pb) / arr.el_size;

    mysort(arr.pb, number_count, arr.el_size, int_cmp);

    rc = fprint_dyn_arr(&arr, args.file_out);

    fclose(args.file_out);
    dyn_arr_destroy(&arr); // free внутри

    if (rc)
    {
#ifndef LDL
        return PRINT_ERROR + rc;
#else
        rc = PRINT_ERROR + rc;
        goto free_lib;
#endif
    }

#ifdef LDL
free_lib:
    dlclose(dynarrlib);
#endif

    return rc;
}
