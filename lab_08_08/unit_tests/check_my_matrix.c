#include "my_matrix.h"
#include <check.h>

void matrix_fill(matrix_t *mat)
{
    for (size_t i = 0; i < mat->rows; ++i)
        for (size_t j = 0; j < mat->columns; ++j)
            matrix_set(mat, i, j, i * mat->columns + j);
}

START_TEST(test_init_ok)
{
    int rc;
    int32_t zeroarr[] = {0, 0, 0, 0, 0};
    matrix_t mat;

    rc = matrix_init(&mat, 5, 5);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(mat.rows, 5);
    ck_assert_int_eq(mat.columns, 5);

    ck_assert_mem_eq(mat.rowsptr[0], zeroarr, sizeof(zeroarr));
    ck_assert_mem_eq(mat.rowsptr[1], zeroarr, sizeof(zeroarr));
    ck_assert_mem_eq(mat.rowsptr[2], zeroarr, sizeof(zeroarr));
    ck_assert_mem_eq(mat.rowsptr[3], zeroarr, sizeof(zeroarr));
    ck_assert_mem_eq(mat.rowsptr[4], zeroarr, sizeof(zeroarr));

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_set)
{
    matrix_t mat;
    matrix_init(&mat, 3, 3);

    matrix_set(&mat, 1, 1, 2);
    int32_t val = matrix_get(&mat, 1, 1);

    ck_assert_int_eq(val, 2);

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_get_w_set)
{
    matrix_t mat;
    matrix_init(&mat, 3, 3);

    matrix_set(&mat, 1, 1, 2);
    int32_t val = matrix_get(&mat, 1, 1);

    ck_assert_int_eq(val, 2);

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_get)
{
    matrix_t mat;
    matrix_init(&mat, 3, 3);

    matrix_fill(&mat);

    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            ck_assert_int_eq(i * mat.columns + j, matrix_get(&mat, i, j));

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_row_min)
{
    matrix_t mat;
    matrix_init(&mat, 3, 3);

    matrix_fill(&mat);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_int_eq(i * mat.columns, matrix_row_min(&mat, i));

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_col_min)
{
    matrix_t mat;
    matrix_init(&mat, 3, 3);

    matrix_fill(&mat);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_int_eq(i, matrix_col_min(&mat, i));

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_col_geom_avg)
{
    matrix_t mat;
    int32_t res[] = {0, 7, 9, 10, 11};
    matrix_init(&mat, 5, 5);

    matrix_fill(&mat);

    for (size_t i = 0; i < 5; ++i)
        ck_assert_int_eq(res[i], matrix_col_geom_avg(&mat, i));

    matrix_destroy(&mat);
}
END_TEST

START_TEST(test_copy_eqs)
{
    matrix_t mat1, mat2;
    matrix_init(&mat1, 5, 5);
    matrix_init(&mat2, 5, 5);

    matrix_fill(&mat1);
    matrix_copy(&mat1, &mat2);

    ck_assert_uint_eq(mat1.columns, mat2.columns);
    ck_assert_uint_eq(mat1.rows, mat2.rows);

    for (size_t i = 0; i < 5; ++i)
        ck_assert_mem_eq(mat1.rowsptr[i], mat2.rowsptr[i], sizeof(int32_t) * 5);

    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}
END_TEST

START_TEST(test_copy_ls)
{
    matrix_t mat1, mat2;
    matrix_init(&mat1, 5, 5);
    matrix_init(&mat2, 3, 3);

    matrix_fill(&mat1);
    matrix_copy(&mat1, &mat2);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(mat1.rowsptr[i], mat2.rowsptr[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}
END_TEST

START_TEST(test_copy_gs)
{
    matrix_t mat1, mat2;
    int32_t zeros[] = {0, 0, 0, 0, 0};

    matrix_init(&mat1, 3, 3);
    matrix_init(&mat2, 5, 5);

    matrix_fill(&mat1);
    matrix_copy(&mat1, &mat2);

    for (size_t i = 0; i < 3; ++i)
    {
        ck_assert_mem_eq(mat1.rowsptr[i], mat2.rowsptr[i], sizeof(int32_t) * 3);
        ck_assert_mem_eq(&mat2.rowsptr[i][3], zeros, sizeof(int32_t) * 2);
    }
    ck_assert_mem_eq(mat2.rowsptr[3], zeros, sizeof(int32_t) * 5);
    ck_assert_mem_eq(mat2.rowsptr[4], zeros, sizeof(int32_t) * 5);

    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}
END_TEST

START_TEST(test_sqarify_horizontal)
{
    matrix_t mat1;
    int32_t target[3][3] = {
    {2, 3, 4},
    {7, 8, 9},
    {12, 13, 14},
    };

    matrix_init(&mat1, 3, 5);

    matrix_fill(&mat1);

    matrix_squarify(&mat1);

    ck_assert_uint_eq(mat1.columns, mat1.rows);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(mat1.rowsptr[i], target[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
}
END_TEST

START_TEST(test_sqarify_vertical)
{
    matrix_t mat1;
    int32_t target[3][3] = {
    {6, 7, 8},
    {9, 10, 11},
    {12, 13, 14},
    };

    matrix_init(&mat1, 5, 3);

    matrix_fill(&mat1);

    matrix_squarify(&mat1);

    ck_assert_uint_eq(mat1.columns, mat1.rows);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(mat1.rowsptr[i], target[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
}
END_TEST

START_TEST(test_mul_square)
{
    matrix_t mat1, res;
    int32_t target[3][3] = {
    {15, 18, 21},
    {42, 54, 66},
    {69, 90, 111},
    };

    matrix_init(&mat1, 3, 3);

    matrix_fill(&mat1);

    matrix_mul(&mat1, &mat1, &res);

    ck_assert_uint_eq(mat1.columns, res.columns);
    ck_assert_uint_eq(mat1.rows, res.rows);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(target[i], res.rowsptr[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
    matrix_destroy(&res);
}
END_TEST

START_TEST(test_mul_normal)
{
    matrix_t mat1, mat2, res;
    int32_t target[3][3] = {
    {90, 100, 110},
    {240, 275, 310},
    {390, 450, 510},
    };

    matrix_init(&mat1, 3, 5);
    matrix_init(&mat2, 5, 3);

    matrix_fill(&mat1);
    matrix_fill(&mat2);

    matrix_mul(&mat1, &mat2, &res);

    ck_assert_uint_eq(mat1.rows, res.rows);
    ck_assert_uint_eq(mat2.columns, res.columns);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(target[i], res.rowsptr[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&res);
}
END_TEST

START_TEST(test_pow_square)
{
    matrix_t mat1, res;
    int32_t target[3][3] = {
    {15, 18, 21},
    {42, 54, 66},
    {69, 90, 111},
    };

    matrix_init(&mat1, 3, 3);

    matrix_fill(&mat1);

    matrix_pow(&mat1, 2, &res);

    ck_assert_uint_eq(mat1.columns, res.columns);
    ck_assert_uint_eq(mat1.rows, res.rows);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(target[i], res.rowsptr[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
    matrix_destroy(&res);
}
END_TEST

START_TEST(test_pow_3)
{
    matrix_t mat1, res;
    int32_t target[3][3] = {
    {180, 234, 288},
    {558, 720, 882},
    {936, 1206, 1476},
    };

    matrix_init(&mat1, 3, 3);

    matrix_fill(&mat1);

    matrix_pow(&mat1, 3, &res);

    ck_assert_uint_eq(mat1.columns, res.columns);
    ck_assert_uint_eq(mat1.rows, res.rows);

    for (size_t i = 0; i < 3; ++i)
        ck_assert_mem_eq(target[i], res.rowsptr[i], sizeof(int32_t) * 3);

    matrix_destroy(&mat1);
    matrix_destroy(&res);
}

START_TEST(test_unify)
{
    matrix_t mat1, mat2;

    matrix_init(&mat1, 3, 3);
    matrix_init(&mat2, 5, 5);

    matrix_fill(&mat1);
    matrix_fill(&mat2);

    matrix_unify(&mat1, &mat2);

    int32_t target[5][5] = {
    {0, 1, 2, 0, 0},
    {3, 4, 5, 3, 3},
    {6, 7, 8, 6, 6},
    {0, 3, 4, 0, 0},
    {0, 3, 4, 0, 0},
    };

    ck_assert_uint_eq(mat1.columns, mat2.columns);
    ck_assert_uint_eq(mat1.rows, mat2.rows);

    for (size_t i = 0; i < 5; ++i)
        ck_assert_mem_eq(mat1.rowsptr[i], target[i], sizeof(int32_t) * 5);

    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}
END_TEST

Suite *my_matrix_suite(void)
{
    Suite *s;
    TCase *tc_init, *tc_get, *tc_set, *tc_row_min, *tc_col_min,
    *tc_col_geom_avg, *tc_copy, *tc_squarify, *tc_unify, *tc_mul, *tc_pow;

    s = suite_create("my_matrix");

    tc_init = tcase_create("matrix_init");
    tc_get = tcase_create("matrix_get");
    tc_set = tcase_create("matrix_set");
    tc_row_min = tcase_create("matrix_row_min");
    tc_col_min = tcase_create("matrix_col_min");
    tc_col_geom_avg = tcase_create("matrix_col_geom_avg");
    tc_copy = tcase_create("matrix_copy");
    tc_squarify = tcase_create("matrix_squarify");
    tc_mul = tcase_create("matrix_mul");
    tc_pow = tcase_create("matrix_pow");

    tc_unify = tcase_create("matrix_unify");

    tcase_add_test(tc_init, test_init_ok);

    tcase_add_test(tc_set, test_set);

    tcase_add_test(tc_get, test_get);
    tcase_add_test(tc_get, test_get_w_set);

    tcase_add_test(tc_row_min, test_row_min);

    tcase_add_test(tc_col_min, test_col_min);

    tcase_add_test(tc_col_geom_avg, test_col_geom_avg);

    tcase_add_test(tc_copy, test_copy_eqs);
    tcase_add_test(tc_copy, test_copy_ls);
    tcase_add_test(tc_copy, test_copy_gs);

    tcase_add_test(tc_squarify, test_sqarify_horizontal);
    tcase_add_test(tc_squarify, test_sqarify_vertical);

    tcase_add_test(tc_mul, test_mul_square);
    tcase_add_test(tc_mul, test_mul_normal);

    tcase_add_test(tc_pow, test_pow_square);
    tcase_add_test(tc_pow, test_pow_3);

    tcase_add_test(tc_unify, test_unify);

    suite_add_tcase(s, tc_init);
    suite_add_tcase(s, tc_get);
    suite_add_tcase(s, tc_set);
    suite_add_tcase(s, tc_row_min);
    suite_add_tcase(s, tc_col_min);
    suite_add_tcase(s, tc_col_geom_avg);
    suite_add_tcase(s, tc_copy);
    suite_add_tcase(s, tc_squarify);
    suite_add_tcase(s, tc_unify);
    suite_add_tcase(s, tc_mul);
    suite_add_tcase(s, tc_pow);

    return s;
}
