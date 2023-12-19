#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *check_assoc_arr(void);

int main(void)
{
    int number_failed = 0;

    Suite *s;
    SRunner *sr;

    s = check_assoc_arr();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);

    srunner_free(sr);

    return number_failed;
}
