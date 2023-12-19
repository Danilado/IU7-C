#include "item.h"
#include <check.h>

START_TEST(test_item_init)
{
    item_t item = item_create();

    ck_assert_ptr_eq(NULL, item_get_name(item));
    ck_assert_double_eq(1.0, item_get_weight(item));
    ck_assert_double_eq(1.0, item_get_volume(item));

    item_destroy(item);
}
END_TEST

START_TEST(test_name_getset)
{
    item_t item = item_create();
    char *name = calloc(20, sizeof(char));
    sprintf(name, "ITEM_NAME_TEST");

    item_set_name(item, name);

    ck_assert_pstr_eq(name, item_get_name(item));
    ck_assert_ptr_eq(name, item_get_name(item));
    ck_assert_str_eq("ITEM_NAME_TEST", item_get_name(item));

    item_destroy(item);
}
END_TEST

START_TEST(test_weight_getset)
{
    item_t item = item_create();

    item_set_weight(item, 2.0);
    ck_assert_double_eq(2.0, item_get_weight(item));

    item_destroy(item);
}
END_TEST

START_TEST(test_volume_getset)
{
    item_t item = item_create();

    item_set_volume(item, 2.0);
    ck_assert_double_eq(2.0, item_get_volume(item));

    item_destroy(item);
}
END_TEST

START_TEST(test_get_density_1)
{
    item_t item = item_create();

    item_set_weight(item, 2.0);
    item_set_volume(item, 2.0);

    ck_assert_double_eq(
    item_get_density(item), item_get_weight(item) / item_get_volume(item));
    ck_assert_double_eq(item_get_density(item), 2.0 / 2.0);

    item_destroy(item);
}
END_TEST
START_TEST(test_get_density_2)
{
    item_t item = item_create();

    item_set_weight(item, 1.0);
    item_set_volume(item, 2.0);

    ck_assert_double_eq(
    item_get_density(item), item_get_weight(item) / item_get_volume(item));
    ck_assert_double_eq(item_get_density(item), 1.0 / 2.0);

    item_destroy(item);
}
END_TEST
START_TEST(test_get_density_3)
{
    item_t item = item_create();

    item_set_weight(item, 2.0);
    item_set_volume(item, 1.0);

    ck_assert_double_eq(
    item_get_density(item), item_get_weight(item) / item_get_volume(item));
    ck_assert_double_eq(item_get_density(item), 2.0 / 1.0);

    item_destroy(item);
}
END_TEST

Suite *check_item_suite(void)
{
    Suite *s;
    TCase *tc_init, *tc_name, *tc_weight, *tc_volume, *tc_density;

    s = suite_create("item");

    tc_init = tcase_create("item init");
    tc_name = tcase_create("name getset");
    tc_weight = tcase_create("weight getset");
    tc_volume = tcase_create("volume getset");
    tc_density = tcase_create("get_density");

    tcase_add_test(tc_init, test_item_init);

    tcase_add_test(tc_name, test_name_getset);
    tcase_add_test(tc_weight, test_weight_getset);
    tcase_add_test(tc_volume, test_volume_getset);

    tcase_add_test(tc_density, test_get_density_1);
    tcase_add_test(tc_density, test_get_density_2);
    tcase_add_test(tc_density, test_get_density_3);

    suite_add_tcase(s, tc_init);
    suite_add_tcase(s, tc_name);
    suite_add_tcase(s, tc_weight);
    suite_add_tcase(s, tc_volume);
    suite_add_tcase(s, tc_density);

    return s;
}