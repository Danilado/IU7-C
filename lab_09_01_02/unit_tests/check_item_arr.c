#include "item_arr.h"
#include <check.h>

START_TEST(test_item_arr_init)
{
    item_arr_t arr = item_arr_create();

    ck_assert_uint_eq(0, item_arr_get_length(arr));
    ck_assert_uint_eq(0, item_arr_get_capacity(arr));

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_expand)
{
    item_arr_t arr = item_arr_create();

    int rc = item_arr_expand(arr);

    ck_assert_int_eq(rc, 0);
    ck_assert_uint_eq(item_arr_get_length(arr), 0);
    ck_assert_uint_eq(item_arr_get_capacity(arr), 1);

    for (size_t i = 0; i < 10; i++)
    {
        rc = item_arr_expand(arr);
        ck_assert_int_eq(rc, 0);
    }

    ck_assert_uint_eq(item_arr_get_length(arr), 0);
    ck_assert_uint_eq(item_arr_get_capacity(arr), 15);

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_minimize)
{
    item_arr_t arr = item_arr_create();
    int rc;

    item_t item = item_create();
    rc = item_arr_push(arr, item);
    ck_assert_int_eq(rc, 0);

    for (size_t i = 0; i < 10; i++)
    {
        rc = item_arr_expand(arr);
        ck_assert_int_eq(rc, 0);
    }

    ck_assert_uint_eq(item_arr_get_length(arr), 1);
    ck_assert_uint_eq(item_arr_get_capacity(arr), 15);

    rc = item_arr_minimize(arr);

    ck_assert_int_eq(rc, 0);
    ck_assert_uint_eq(item_arr_get_length(arr), 1);
    ck_assert_uint_eq(item_arr_get_capacity(arr), 1);

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_push_1)
{
    item_arr_t arr = item_arr_create();
    int rc;

    item_t item = item_create();
    rc = item_arr_push(arr, item);
    ck_assert_int_eq(rc, 0);

    ck_assert_uint_eq(item_arr_get_length(arr), 1);
    ck_assert_uint_eq(item_arr_get_capacity(arr), 1);

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_push_11)
{
    item_arr_t arr = item_arr_create();
    int rc;

    for (size_t i = 0; i < 11; i++)
    {
        item_t item = item_create();
        rc = item_arr_push(arr, item);
        ck_assert_int_eq(rc, 0);
    }

    ck_assert_uint_eq(item_arr_get_length(arr), 11);
    ck_assert_uint_eq(item_arr_get_capacity(arr), 11);

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_get)
{
    item_arr_t arr = item_arr_create();
    int rc;

    item_t item = item_create();
    rc = item_arr_push(arr, item);
    ck_assert_int_eq(rc, 0);

    ck_assert_ptr_eq(item_arr_get_by_index(arr, 0), item);

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_get_null)
{
    item_arr_t arr = item_arr_create();
    int rc;

    item_t item = item_create();
    rc = item_arr_push(arr, item);
    ck_assert_int_eq(rc, 0);

    ck_assert_ptr_eq(item_arr_get_by_index(arr, 100), NULL);

    item_arr_destroy(arr);
}
END_TEST

START_TEST(test_sort)
{
    item_arr_t arr = item_arr_create();
    int rc;

    for (size_t i = 0; i < 10; ++i)
    {
        item_t item = item_create();
        item_set_weight(item, 10.0 - i);
        item_set_volume(item, 1.0);
        rc = item_arr_push(arr, item);
        ck_assert_int_eq(rc, 0);
    }

    sort_by_density(arr);

    for (size_t i = 0; i < 10; ++i)
        ck_assert_double_eq(
        item_get_weight(item_arr_get_by_index(arr, i)), (double)i + 1.0);

    item_arr_destroy(arr);
}
END_TEST

Suite *check_item_arr_suite(void)
{
    Suite *s;
    TCase *tc_init, *tc_push, *tc_expand, *tc_minimize, *tc_get, *tc_sort;

    s = suite_create("item_arr");

    tc_init = tcase_create("test init");
    tc_push = tcase_create("test push");
    tc_expand = tcase_create("test expand");
    tc_minimize = tcase_create("test minimize");
    tc_get = tcase_create("test get by index");
    tc_sort = tcase_create("test sort");

    tcase_add_test(tc_init, test_item_arr_init);
    tcase_add_test(tc_push, test_push_1);
    tcase_add_test(tc_push, test_push_11);
    tcase_add_test(tc_expand, test_expand);
    tcase_add_test(tc_minimize, test_minimize);
    tcase_add_test(tc_get, test_get);
    tcase_add_test(tc_get, test_get_null);
    tcase_add_test(tc_sort, test_sort);

    suite_add_tcase(s, tc_init);
    suite_add_tcase(s, tc_push);
    suite_add_tcase(s, tc_expand);
    suite_add_tcase(s, tc_minimize);
    suite_add_tcase(s, tc_get);
    suite_add_tcase(s, tc_sort);

    return s;
}