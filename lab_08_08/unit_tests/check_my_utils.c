#include "my_utils.h"
#include <check.h>

START_TEST(test_max_int_g)
{
    int res;
    res = MAX(2, 1);
    ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(test_max_int_l)
{
    int res;
    res = MAX(1, 2);
    ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(test_max_int_eq)
{
    int res;
    res = MAX(1, 1);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_max_double_g)
{
    double res;
    double a = 2.0, b = 1.0;
    res = MAX(a, b);
    ck_assert_double_eq(res, a);
}
END_TEST

START_TEST(test_max_double_l)
{
    double res;
    double a = 1.0, b = 2.0;
    res = MAX(a, b);
    ck_assert_double_eq(res, b);
}
END_TEST

START_TEST(test_max_double_eq)
{
    double res;
    double a = 2.0, b = 2.0;
    res = MAX(a, b);
    ck_assert_double_eq(res, b);
}
END_TEST

START_TEST(test_min_int_g)
{
    int res;
    res = MIN(2, 1);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_min_int_l)
{
    int res;
    res = MIN(1, 2);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_min_int_eq)
{
    int res;
    res = MIN(1, 1);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_min_double_g)
{
    double res;
    double a = 2.0, b = 1.0;
    res = MIN(a, b);
    ck_assert_double_eq(res, b);
}
END_TEST

START_TEST(test_min_double_l)
{
    double res;
    double a = 1.0, b = 2.0;
    res = MIN(a, b);
    ck_assert_double_eq(res, a);
}
END_TEST

START_TEST(test_min_double_eq)
{
    double res;
    double a = 2.0, b = 2.0;
    res = MIN(a, b);
    ck_assert_double_eq(res, b);
}
END_TEST

Suite *my_utils_suite(void)
{
    Suite *s;
    TCase *tc_max, *tc_min;

    s = suite_create("my_utils");

    tc_max = tcase_create("max");
    tc_min = tcase_create("min");

    tcase_add_test(tc_max, test_max_int_g);
    tcase_add_test(tc_max, test_max_int_l);
    tcase_add_test(tc_max, test_max_int_eq);
    tcase_add_test(tc_max, test_max_double_g);
    tcase_add_test(tc_max, test_max_double_l);
    tcase_add_test(tc_max, test_max_double_eq);

    tcase_add_test(tc_min, test_min_int_g);
    tcase_add_test(tc_min, test_min_int_l);
    tcase_add_test(tc_min, test_min_int_eq);
    tcase_add_test(tc_min, test_min_double_g);
    tcase_add_test(tc_min, test_min_double_l);
    tcase_add_test(tc_min, test_min_double_eq);

    suite_add_tcase(s, tc_max);
    suite_add_tcase(s, tc_min);

    return s;
}
