#include "my_dynamic_arr.h"
#include <check.h>

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
