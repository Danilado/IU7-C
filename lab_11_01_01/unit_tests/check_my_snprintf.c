#include "my_snprintf.h"
#include <check.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma GCC diagnostic push
// Я специально проверяю это поведение
#pragma GCC diagnostic ignored "-Wformat-truncation"
#pragma GCC diagnostic ignored "-Wformat-zero-length"

START_TEST(test_empty_format)
{
    char *buf = calloc(10, sizeof(char));
    int rc1, rc2;
    rc1 = snprintf(buf, 100, "");
    rc2 = my_snprintf(buf, 100, "");

    ck_assert_int_eq(0, rc1);
    ck_assert_int_eq(0, rc2);
    free(buf);
}
END_TEST

START_TEST(test_zerolen)
{
    char *buf = calloc(10, sizeof(char));
    int rc1, rc2;
    rc1 = snprintf(buf, 0, "");
    ck_assert_int_eq(0, rc1);

    rc2 = my_snprintf(buf, 0, "");
    ck_assert_int_eq(0, rc2);
    ck_assert_int_eq(buf[0], 0);
    free(buf);
}
END_TEST

START_TEST(test_unsupported_format)
{
    char *buf = calloc(10, sizeof(char));
    int rc = my_snprintf(buf, 10, "%zu");

    ck_assert_int_eq(rc, -UNSUPPORTED_FORMAT);
    free(buf);
}
END_TEST

START_TEST(test_int_zero)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%d", 0);
    int rc2 = my_snprintf(buf2, 99, "%d", 0);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_int_normal)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%d", 42);
    int rc2 = my_snprintf(buf2, 99, "%d", 42);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_int_negative)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%d", -42);
    int rc2 = my_snprintf(buf2, 99, "%d", -42);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_int_min)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%d", INT_MIN);
    int rc2 = my_snprintf(buf2, 99, "%d", INT_MIN);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_int_multiple)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%d%d%d%d", 42, 42, 42, 42);
    int rc2 = my_snprintf(buf2, 99, "%d%d%d%d", 42, 42, 42, 42);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_int_cutoff)
{
    char *buf1 = calloc(2, sizeof(char));
    char *buf2 = calloc(2, sizeof(char));

    int rc1 = snprintf(buf1, 1, "%d%d%d%d", 42, 42, 42, 42);
    int rc2 = my_snprintf(buf2, 1, "%d%d%d%d", 42, 42, 42, 42);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_str_zero)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%s", "");
    int rc2 = my_snprintf(buf2, 99, "%s", "");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_str_normal)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%s", "chislo 42");
    int rc2 = my_snprintf(buf2, 99, "%s", "chislo 42");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_str_multiple)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "%s%s%s%s", "42!", "42!", "42!", "42!");
    int rc2 = my_snprintf(buf2, 99, "%s%s%s%s", "42!", "42!", "42!", "42!");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_str_cutoff)
{
    char *buf1 = calloc(6, sizeof(char));
    char *buf2 = calloc(6, sizeof(char));

    int rc1 = snprintf(buf1, 5, "%s%s%s%s", "42!", "42!", "42!", "42!");
    int rc2 = my_snprintf(buf2, 5, "%s%s%s%s", "42!", "42!", "42!", "42!");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_pt_sprint)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "The number 42");
    int rc2 = my_snprintf(buf2, 99, "The number 42");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_pt_percent)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(buf1, 99, "The number 42%%");
    int rc2 = my_snprintf(buf2, 99, "The number 42%%");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf2);
    free(buf1);
}
END_TEST

START_TEST(test_pt_cutoff)
{
    char *buf1 = calloc(5, sizeof(char));
    char *buf2 = calloc(5, sizeof(char));

    int rc1 = snprintf(buf1, 5, "The number 42%%");
    int rc2 = my_snprintf(buf2, 5, "The number 42%%");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_comb_normal)
{
    char *buf1 = calloc(100, sizeof(char));
    char *buf2 = calloc(100, sizeof(char));

    int rc1 = snprintf(
    buf1, 99, "%s is at the number %d in the table", "Letter 'P'", (int)'P');
    int rc2 = my_snprintf(
    buf2, 99, "%s is at the number %d in the table", "Letter 'P'", (int)'P');

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_comb_cutoff)
{
    char *buf1 = calloc(10, sizeof(char));
    char *buf2 = calloc(10, sizeof(char));

    int rc1 = snprintf(
    buf1, 9, "%s is the on the number %d in the table", "Letter 'P'", (int)'P');
    int rc2 = my_snprintf(
    buf2, 9, "%s is the on the number %d in the table", "Letter 'P'", (int)'P');

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
    free(buf1);
    free(buf2);
}
END_TEST

Suite *check_my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_bad_args, *tc_int, *tc_string, *tc_plain_text, *tc_combined;

    s = suite_create("my_snpritf");

    tc_bad_args = tcase_create("bad_args");
    tc_int = tcase_create("int");
    tc_string = tcase_create("string");
    tc_plain_text = tcase_create("plain_text");
    tc_combined = tcase_create("combined");

    tcase_add_test(tc_bad_args, test_empty_format);
    tcase_add_test(tc_bad_args, test_zerolen);
    tcase_add_test(tc_bad_args, test_unsupported_format);

    tcase_add_test(tc_int, test_int_zero);
    tcase_add_test(tc_int, test_int_normal);
    tcase_add_test(tc_int, test_int_negative);
    tcase_add_test(tc_int, test_int_min);
    tcase_add_test(tc_int, test_int_multiple);
    tcase_add_test(tc_int, test_int_cutoff);

    tcase_add_test(tc_string, test_str_zero);
    tcase_add_test(tc_string, test_str_normal);
    tcase_add_test(tc_string, test_str_multiple);
    tcase_add_test(tc_string, test_str_cutoff);

    tcase_add_test(tc_plain_text, test_pt_sprint);
    tcase_add_test(tc_plain_text, test_pt_percent);
    tcase_add_test(tc_plain_text, test_pt_cutoff);

    tcase_add_test(tc_combined, test_comb_normal);
    tcase_add_test(tc_combined, test_comb_cutoff);

    suite_add_tcase(s, tc_bad_args);
    suite_add_tcase(s, tc_int);
    suite_add_tcase(s, tc_string);
    suite_add_tcase(s, tc_plain_text);
    suite_add_tcase(s, tc_combined);

    return s;
}

#pragma GCC diagnostic pop
