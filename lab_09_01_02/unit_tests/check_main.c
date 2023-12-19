#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *check_item_suite(void);
Suite *check_item_arr_suite(void);

int main(void)
{
    int number_failed = 0;

    Suite *s;
    SRunner *sr;

    s = check_item_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    srunner_free(sr);

    s = check_item_arr_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    srunner_free(sr);

    return number_failed;
}
