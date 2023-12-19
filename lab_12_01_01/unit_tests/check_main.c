#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LDL
#include "dynarr.h"
#else
#include "check_common.h"
fn_count_numbers_in_file_t count_numbers_in_file;
fn_dyn_arr_init_t dyn_arr_init;
fn_fill_dyn_arr_from_file_t fill_dyn_arr_from_file;
fn_dyn_arr_destroy_t dyn_arr_destroy;
fn_key_t key;
fn_mysort_t mysort;
fn_fprint_dyn_arr_t fprint_dyn_arr;
fn_int_cmp_t int_cmp;
fn_swap_t swap;
#endif

Suite *dynarr_suite(void);
Suite *myfuncs_suite(void);

enum error_classes
{
    ERROR_IN_ARGPARSE = 0,
    SCAN_ERROR = 10,
    DYN_ARR_ERROR = 20,
    PROCESSING_ERROR = 30,
    PRINT_ERROR = 40,
    LDL_ERROR = 50,
};

int main(void)
{
#ifdef LDL
    void *dynarrlib;
    dynarrlib = dlopen("./out/libdynarr.so", RTLD_NOW);
    if (!dynarrlib)
    {
        printf("Cannot open library. err: %s\n", dlerror());
        exit(LDL_ERROR + 1);
    }

    count_numbers_in_file =
    (fn_count_numbers_in_file_t)dlsym(dynarrlib, "count_numbers_in_file");
    if (!count_numbers_in_file)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    dyn_arr_init = (fn_dyn_arr_init_t)dlsym(dynarrlib, "dyn_arr_init");
    if (!dyn_arr_init)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    fill_dyn_arr_from_file =
    (fn_fill_dyn_arr_from_file_t)dlsym(dynarrlib, "fill_dyn_arr_from_file");
    if (!fill_dyn_arr_from_file)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    dyn_arr_destroy = (fn_dyn_arr_destroy_t)dlsym(dynarrlib, "dyn_arr_destroy");
    if (!dyn_arr_destroy)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    key = (fn_key_t)dlsym(dynarrlib, "key");
    if (!key)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    mysort = (fn_mysort_t)dlsym(dynarrlib, "mysort");
    if (!mysort)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    fprint_dyn_arr = (fn_fprint_dyn_arr_t)dlsym(dynarrlib, "fprint_dyn_arr");
    if (!fprint_dyn_arr)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    int_cmp = (fn_int_cmp_t)dlsym(dynarrlib, "int_cmp");
    if (!int_cmp)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }

    swap = (fn_swap_t)dlsym(dynarrlib, "swap");
    if (!swap)
    {
        printf("Error fetching function. err: %s", dlerror());
        exit(LDL_ERROR + 2);
    }
#endif

    int number_failed;
    Suite *s;
    SRunner *sr;

    s = dynarr_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    s = myfuncs_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    srunner_free(sr);

#ifdef LDL
    dlclose(dynarrlib);
#endif

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
