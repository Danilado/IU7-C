#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LDL
#include "dynarr.h"
#else
#include "check_common.h"

#endif

START_TEST(test_dynamic_arr_no_memory)
{
    int rc;
    my_dyn_arr_t tmp;

    rc = dyn_arr_init(SIZE_MAX, SIZE_MAX, &tmp);
    ck_assert_int_eq(rc, NOT_ENOUGH_MEMORY);
}
END_TEST

START_TEST(test_dynamic_arr_one_integer)
{
    int rc;
    my_dyn_arr_t tmp;
    int tmpint = 0;

    rc = dyn_arr_init(sizeof(int), 1, &tmp);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_mem_eq(tmp.pb, &tmpint, sizeof(int));

    dyn_arr_destroy(&tmp);
}
END_TEST

Suite *dynarr_suite(void)
{
    Suite *s;
    TCase *tc_dynarr;

    s = suite_create("dyn_arr");

    tc_dynarr = tcase_create("dynarr");

    tcase_add_test(tc_dynarr, test_dynamic_arr_no_memory);
    tcase_add_test(tc_dynarr, test_dynamic_arr_one_integer);

    suite_add_tcase(s, tc_dynarr);

    return s;
}

START_TEST(test_swap_int)
{
    int rc;
    int a[2] = {1, 2}, b[2] = {2, 1};

    rc = swap(&a[0], &a[1], sizeof(a[0]));

    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

START_TEST(test_swap_double)
{
    int rc;

    double c[2] = {1.0, 2.0}, d[2] = {2.0, 1.0};
    rc = swap(&c[0], &c[1], sizeof(c[0]));

    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_mem_eq(c, d, sizeof(c));
}
END_TEST

START_TEST(test_swap_string)
{
    int rc;

    char e[2][5] = {"mama", "papa"}, f[2][5] = {"papa", "mama"};
    rc = swap(&e[0], &e[1], sizeof(e[0]));

    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_mem_eq(e, f, sizeof(e));
}
END_TEST

START_TEST(test_int_cmp_eq)
{
    int rc;
    int arr[] = {1, 1};
    rc = int_cmp(&arr[0], &arr[1]);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_int_cmp_gt)
{
    int rc;
    int arr[] = {2, 1};
    rc = int_cmp(&arr[0], &arr[1]);
    ck_assert_int_gt(rc, 0);
}
END_TEST

START_TEST(test_int_cmp_lt)
{
    int rc;
    int arr[] = {1, 2};
    rc = int_cmp(&arr[0], &arr[1]);
    ck_assert_int_lt(rc, 0);
}
END_TEST

START_TEST(test_key_no_neg_asc)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {1, 2, 3, 4, 5};
    int res[] = {1, 2, 3, 4, 5};

    rc = key(arr, arr + sizeof(arr) / sizeof(arr[0]), &pb, &pe);

    ck_assert_int_eq(rc, 0);
    for (size_t i = 0; i < sizeof(res) / sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], pb[i]);

    free(pb);
}
END_TEST

START_TEST(test_key_no_neg_desc)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {5, 4, 3, 2, 1};
    int res[] = {5, 4, 3, 2, 1};

    rc = key(arr, arr + sizeof(arr) / sizeof(arr[0]), &pb, &pe);

    ck_assert_int_eq(rc, 0);
    for (size_t i = 0; i < sizeof(res) / sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], pb[i]);

    free(pb);
}
END_TEST

START_TEST(test_key_one_left)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {1, -2, 3, 4, 5};
    int res[] = {1};

    rc = key(arr, arr + sizeof(arr) / sizeof(arr[0]), &pb, &pe);

    ck_assert_int_eq(rc, 0);
    for (size_t i = 0; i < sizeof(res) / sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], pb[i]);

    free(pb);
}
END_TEST

START_TEST(test_key_two_left)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {1, 2, -3, 4, 5};
    int res[] = {1, 2};

    rc = key(arr, arr + sizeof(arr) / sizeof(arr[0]), &pb, &pe);

    ck_assert_int_eq(rc, 0);
    for (size_t i = 0; i < sizeof(res) / sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], pb[i]);

    free(pb);
}
END_TEST

START_TEST(test_key_four_left)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {1, 2, 3, 4, -5};
    int res[] = {1, 2, 3, 4};

    rc = key(arr, arr + sizeof(arr) / sizeof(arr[0]), &pb, &pe);

    ck_assert_int_eq(rc, 0);
    for (size_t i = 0; i < sizeof(res) / sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], pb[i]);

    free(pb);
}
END_TEST

START_TEST(test_key_nothing_left)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {-1, 2, 3, 4, 5};

    rc = key(arr, arr + sizeof(arr) / sizeof(arr[0]), &pb, &pe);

    ck_assert_int_eq(rc, EMPTY_ARRAY);

    free(pb);
}
END_TEST

START_TEST(test_key_bad_input)
{
    int *pb = calloc(5, sizeof(int));
    int *pe = pb + 5;
    int rc;
    int arr[] = {-1, 2, 3, 4, 5};

    rc = key(arr + sizeof(arr) / sizeof(arr[0]), arr, &pb, &pe);

    ck_assert_int_eq(rc, BAD_SRC_PTRS);

    free(pb);
}
END_TEST

START_TEST(test_my_sort_sorted)
{
    int arr[] = {1, 2, 3, 4, 5};
    int res[] = {1, 2, 3, 4, 5};

    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_cmp);

    ck_assert_mem_eq(arr, res, sizeof(res));
}
END_TEST

START_TEST(test_my_sort_unsorted)
{
    int arr[] = {5, 4, 3, 2, 1};
    int res[] = {1, 2, 3, 4, 5};

    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_cmp);

    ck_assert_mem_eq(arr, res, sizeof(res));
}
END_TEST

START_TEST(test_my_sort_borders)
{
    int arr[] = {1, 0, 0, 0, -1};
    int res[] = {-1, 0, 0, 0, 1};

    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_cmp);

    ck_assert_mem_eq(arr, res, sizeof(res));
}
END_TEST

START_TEST(test_my_sort_rnd)
{
    int arr[] = {4, 2, 9, 0, 0};
    int res[] = {0, 0, 2, 4, 9};

    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_cmp);

    ck_assert_mem_eq(arr, res, sizeof(res));
}
END_TEST

START_TEST(test_my_sort_bignums)
{
    int arr[] = {-100, 100, 1000, -10000, 0};
    int res[] = {-10000, -100, 0, 100, 1000};

    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_cmp);

    ck_assert_mem_eq(arr, res, sizeof(res));
}
END_TEST

Suite *myfuncs_suite(void)
{
    Suite *s;
    TCase *tc_swap, *tc_intcmp, *tc_key, *tc_mysort;

    s = suite_create("my_funcs");

    tc_swap = tcase_create("swap");
    tc_intcmp = tcase_create("intcmp");
    tc_key = tcase_create("key");
    tc_mysort = tcase_create("mysort");

    // swap
    tcase_add_test(tc_swap, test_swap_int);
    tcase_add_test(tc_swap, test_swap_double);
    tcase_add_test(tc_swap, test_swap_string);

    // int_cmp
    tcase_add_test(tc_intcmp, test_int_cmp_eq);
    tcase_add_test(tc_intcmp, test_int_cmp_gt);
    tcase_add_test(tc_intcmp, test_int_cmp_lt);

    // key
    tcase_add_test(tc_key, test_key_no_neg_asc);
    tcase_add_test(tc_key, test_key_no_neg_desc);
    tcase_add_test(tc_key, test_key_one_left);
    tcase_add_test(tc_key, test_key_two_left);
    tcase_add_test(tc_key, test_key_four_left);
    tcase_add_test(tc_key, test_key_nothing_left);
    tcase_add_test(tc_key, test_key_bad_input);

    // mysort
    tcase_add_test(tc_mysort, test_my_sort_sorted);
    tcase_add_test(tc_mysort, test_my_sort_unsorted);
    tcase_add_test(tc_mysort, test_my_sort_borders);
    tcase_add_test(tc_mysort, test_my_sort_rnd);
    tcase_add_test(tc_mysort, test_my_sort_bignums);

    suite_add_tcase(s, tc_swap);
    suite_add_tcase(s, tc_intcmp);
    suite_add_tcase(s, tc_key);
    suite_add_tcase(s, tc_mysort);

    return s;
}
