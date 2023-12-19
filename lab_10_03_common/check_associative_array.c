#include "associative_array.h"
#include <check.h>
#include <stdlib.h>
#include <string.h>

START_TEST(test_array_create_destroy)
{
    assoc_array_t dict = assoc_array_create();

    ck_assert_ptr_ne(NULL, dict);

    assoc_array_destroy(&dict);

    ck_assert_ptr_eq(NULL, dict);
}
END_TEST

START_TEST(test_insert_nullptr)
{
    int rc;
    rc = assoc_array_insert(NULL, "key", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_insert_bad_key)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));

    int rc;
    rc = assoc_array_insert(dict, key, 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_insert_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));

    strncpy(key, "test_key_1", 20);

    int rc;
    int var = 0;
    rc = assoc_array_insert(dict, key, var);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_insert_duplicate_key)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));

    strncpy(key, "test_key_1", 20);

    int rc;
    rc = assoc_array_insert(dict, key, 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(dict, key, 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_find_nulltr)
{
    int *a = NULL;
    int rc = assoc_array_find(NULL, "", &a);
    ck_assert_ptr_eq(NULL, a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_find_bad_key)
{
    assoc_array_t dict = assoc_array_create();
    int *a = NULL;
    char *key = calloc(20 + 1, sizeof(char));
    int rc = assoc_array_find(dict, key, &a);
    ck_assert_ptr_eq(NULL, a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_find_nf)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));

    strncpy(key, "test_key_1", 20);

    int rc;
    int *a = NULL;
    assoc_array_insert(dict, key, 0);

    rc = assoc_array_find(dict, "laptop", &a);

    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_eq(NULL, a);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_find_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));

    strncpy(key, "test_key_1", 20);

    int rc;
    int *a = NULL;
    assoc_array_insert(dict, key, 0);

    rc = assoc_array_find(dict, key, &a);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_ne(NULL, a);
    ck_assert_int_eq(0, *a);

    *a = 100;

    rc = assoc_array_find(dict, key, &a);
    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_ne(NULL, a);
    ck_assert_int_eq(100, *a);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_remove_nullptr)
{
    int rc = assoc_array_remove(NULL, "");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_remove_bad_key)
{
    assoc_array_t dict = assoc_array_create();
    int rc = assoc_array_remove(dict, "");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_remove_nf)
{
    assoc_array_t dict = assoc_array_create();
    int rc = assoc_array_remove(dict, "laptop");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_remove_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));
    strncpy(key, "test_key_1", 20);

    int rc;
    int *a = NULL;
    assoc_array_insert(dict, key, 0);

    rc = assoc_array_find(dict, key, &a);
    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_ne(NULL, a);
    ck_assert_int_eq(0, *a);

    rc = assoc_array_remove(dict, key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    a = NULL;
    rc = assoc_array_find(dict, "test_key_1", &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_eq(NULL, a);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_clear_nullptr)
{
    int rc = assoc_array_clear(NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_clear_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key = calloc(20 + 1, sizeof(char));
    strncpy(key, "test_key_1", 20);

    int rc;
    int *a = NULL;
    assoc_array_insert(dict, key, 0);

    rc = assoc_array_find(dict, key, &a);
    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_ne(NULL, a);
    ck_assert_int_eq(0, *a);

    rc = assoc_array_clear(dict);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    a = NULL;
    rc = assoc_array_find(dict, "test_key_1", &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_eq(NULL, a);

    free(key);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_each_nullptr)
{
    int rc = assoc_array_each(NULL, NULL, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_each_bad_act)
{
    assoc_array_t dict = assoc_array_create();
    int rc = assoc_array_each(NULL, NULL, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&dict);
}
END_TEST

void inc_and_sum(const char *key, int *num, void *param)
{
    (void)key;
    int *par = param;
    (*num)++;
    *par += *num;
}

START_TEST(test_each_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key1 = calloc(20 + 1, sizeof(char));
    char *key2 = calloc(20 + 1, sizeof(char));
    strncpy(key1, "test_key_1", 20);
    strncpy(key2, "test_key_2", 20);

    int rc;
    int *a = NULL;
    int *b = NULL;
    int sum = 0;

    assoc_array_insert(dict, key1, 0);
    assoc_array_insert(dict, key2, 10);

    rc = assoc_array_find(dict, key1, &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_ne(NULL, a);
    ck_assert_int_eq(0, *a);
    rc = assoc_array_find(dict, key2, &b);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_ne(NULL, b);
    ck_assert_int_eq(10, *b);

    rc = assoc_array_each(dict, inc_and_sum, &sum);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    a = NULL;
    rc = assoc_array_find(dict, key1, &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_ne(NULL, a);
    ck_assert_int_eq(1, *a);

    b = NULL;
    rc = assoc_array_find(dict, key2, &b);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_ne(NULL, b);
    ck_assert_int_eq(11, *b);

    ck_assert_int_eq(12, sum);

    free(key1);
    free(key2);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_min_nullptr)
{
    int rc = assoc_array_min(NULL, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_min_zerolength)
{
    assoc_array_t dict = assoc_array_create();
    int *a = NULL;

    int rc = assoc_array_min(dict, &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_eq(a, NULL);

    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_min_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key1 = calloc(20 + 1, sizeof(char));
    char *key2 = calloc(20 + 1, sizeof(char));
    strncpy(key1, "test_key_1", 20);
    strncpy(key2, "test_key_2", 20);

    int rc;
    int *a = NULL;

    assoc_array_insert(dict, key1, 0);
    assoc_array_insert(dict, key2, 10);

    rc = assoc_array_min(dict, &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_ne(a, NULL);
    ck_assert_int_eq(*a, 0);

    free(key1);
    free(key2);
    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_max_nullptr)
{
    int rc = assoc_array_max(NULL, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_max_zerolength)
{
    assoc_array_t dict = assoc_array_create();
    int *a = NULL;

    int rc = assoc_array_max(dict, &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_eq(a, NULL);

    assoc_array_destroy(&dict);
}
END_TEST

START_TEST(test_max_ok)
{
    assoc_array_t dict = assoc_array_create();
    char *key1 = calloc(20 + 1, sizeof(char));
    char *key2 = calloc(20 + 1, sizeof(char));
    strncpy(key1, "test_key_1", 20);
    strncpy(key2, "test_key_2", 20);

    int rc;
    int *a = NULL;

    assoc_array_insert(dict, key1, 0);
    assoc_array_insert(dict, key2, 10);

    rc = assoc_array_max(dict, &a);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_ne(a, NULL);
    ck_assert_int_eq(*a, 10);

    free(key1);
    free(key2);
    assoc_array_destroy(&dict);
}
END_TEST

Suite *check_assoc_arr(void)
{
    Suite *s;
    TCase *tc_array_create_destroy, *tc_insert, *tc_find, *tc_remove, *tc_clear,
    *tc_each, *tc_min, *tc_max;

    s = suite_create("my_assoc_arr");

    {
        tc_array_create_destroy = tcase_create("array_create_destroy");
        tc_insert = tcase_create("insert");
        tc_find = tcase_create("find");
        tc_remove = tcase_create("remove");
        tc_clear = tcase_create("clear");
        tc_each = tcase_create("each");
        tc_min = tcase_create("min");
        tc_max = tcase_create("max");
    }

    {
        tcase_add_test(tc_array_create_destroy, test_array_create_destroy);

        tcase_add_test(tc_insert, test_insert_nullptr);
        tcase_add_test(tc_insert, test_insert_bad_key);
        tcase_add_test(tc_insert, test_insert_ok);
        tcase_add_test(tc_insert, test_insert_duplicate_key);

        tcase_add_test(tc_find, test_find_nulltr);
        tcase_add_test(tc_find, test_find_bad_key);
        tcase_add_test(tc_find, test_find_ok);
        tcase_add_test(tc_find, test_find_nf);

        tcase_add_test(tc_remove, test_remove_nullptr);
        tcase_add_test(tc_remove, test_remove_bad_key);
        tcase_add_test(tc_remove, test_remove_nf);
        tcase_add_test(tc_remove, test_remove_ok);

        tcase_add_test(tc_clear, test_clear_nullptr);
        tcase_add_test(tc_clear, test_clear_ok);

        tcase_add_test(tc_each, test_each_nullptr);
        tcase_add_test(tc_each, test_each_bad_act);
        tcase_add_test(tc_each, test_each_ok);

        tcase_add_test(tc_min, test_min_nullptr);
        tcase_add_test(tc_min, test_min_zerolength);
        tcase_add_test(tc_min, test_min_ok);

        tcase_add_test(tc_max, test_max_nullptr);
        tcase_add_test(tc_max, test_max_zerolength);
        tcase_add_test(tc_max, test_max_ok);
    }

    {
        suite_add_tcase(s, tc_array_create_destroy);
        suite_add_tcase(s, tc_insert);
        suite_add_tcase(s, tc_find);
        suite_add_tcase(s, tc_remove);
        suite_add_tcase(s, tc_clear);
        suite_add_tcase(s, tc_each);
        suite_add_tcase(s, tc_min);
        suite_add_tcase(s, tc_max);
    }

    return s;
}