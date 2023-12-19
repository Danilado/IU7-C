#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *my_matrix_suite(void);
Suite *my_utils_suite(void);

int main(void)
{
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s = my_matrix_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    srunner_free(sr);

    s = my_utils_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    srunner_free(sr);

    return number_failed;
}
