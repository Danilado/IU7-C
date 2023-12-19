#include "my_list.h"
#include <check.h>

START_TEST(test_node_init)
{
    int *a = calloc(1, sizeof(int));
    *a = 3;
    node_t *node = node_create(a);

    ck_assert_ptr_ne(node, NULL);
    ck_assert_ptr_eq(node->data, a);
    ck_assert_ptr_eq(node->next, NULL);

    free(node->data);
    node_destroy(node);
}
END_TEST

START_TEST(test_length)
{
    node_t **head = calloc(1, sizeof(node_t *));

    ck_assert_uint_eq(0, list_get_length(*head));

    int *a = calloc(1, sizeof(int));
    *a = 3;
    node_t *node = node_create(a);

    *head = node;
    ck_assert_uint_eq(1, list_get_length(*head));

    for (size_t i = 0; i < 10; ++i)
    {
        node_t *prev = node;
        node = node_create(a);
        prev->next = node;
        ck_assert_uint_eq(i + 2, list_get_length(*head));
    }

    free(a);
    list_destroy(head);
}
END_TEST

START_TEST(test_push)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    *a = 3;
    node_t *node = node_create(a);

    list_push(head, node);

    ck_assert_ptr_ne(*head, NULL);
    ck_assert_ptr_eq(*head, node);
    ck_assert_uint_eq(list_get_length(*head), 1);

    for (size_t i = 0; i < 10; ++i)
    {
        node_t *tmp = node;
        node = node_create(a);
        list_push(head, node);

        ck_assert_ptr_ne(*head, NULL);
        ck_assert_ptr_eq(tmp->next, node);
        ck_assert_uint_eq(list_get_length(*head), i + 2);
    }

    free(a);
    list_destroy(head);
}
END_TEST

START_TEST(test_push_val)
{
    node_t **head = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 10; ++i)
    {
        int *a = calloc(1, sizeof(int));
        *a = i;
        int rc = list_push_value(head, a);

        ck_assert_int_eq(rc, 0);
        ck_assert_ptr_ne(*head, NULL);
        ck_assert_uint_eq(list_get_length(*head), i + 1);
    }
    node_t *cur = *head;

    for (size_t i = 0; i < 10; ++i)
    {
        ck_assert_int_eq(*(int *)cur->data, i);
        free(cur->data);
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_pop)
{
    node_t **head = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 10; ++i)
    {
        int *a = calloc(1, sizeof(int));
        *a = i;
        list_push_value(head, a);
    }

    int ref = 9;

    while (*head)
    {
        node_t *last = list_pop(head);
        ck_assert_int_eq(*(int *)last->data, ref);
        free(last->data);
        node_destroy(last);
        ref--;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_unshift)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    *a = 3;
    node_t *node = node_create(a);

    list_push(head, node);

    ck_assert_ptr_ne(*head, NULL);
    ck_assert_ptr_eq(*head, node);
    ck_assert_uint_eq(list_get_length(*head), 1);

    for (size_t i = 0; i < 10; ++i)
    {
        node = node_create(a);
        list_unshift(head, node);

        ck_assert_ptr_ne(*head, NULL);
        ck_assert_ptr_eq(*head, node);
        ck_assert_uint_eq(list_get_length(*head), i + 2);
    }

    free(a);
    list_destroy(head);
}
END_TEST

START_TEST(test_unshift_val)
{
    node_t **head = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 10; ++i)
    {
        int *a = calloc(1, sizeof(int));
        *a = i;
        list_unshift_value(head, a);

        ck_assert_ptr_ne(*head, NULL);
        ck_assert_uint_eq(list_get_length(*head), i + 1);
    }

    node_t *cur = *head;
    int ref = 9;

    for (size_t i = 0; i < 10; ++i)
    {
        ck_assert_int_eq(*(int *)cur->data, ref);
        free(cur->data);
        cur = cur->next;
        --ref;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_shift)
{
    node_t **head = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 10; ++i)
    {
        int *a = calloc(1, sizeof(int));
        *a = i;
        list_unshift_value(head, a);
    }

    int ref = 0;

    while (*head)
    {
        node_t *first = list_pop(head);
        ck_assert_int_eq(*(int *)first->data, ref);
        free(first->data);
        node_destroy(first);
        ref++;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_insert)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    int rc = list_insert(head, node_b, 10000);
    ck_assert_int_ne(rc, 0);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        node_t *tmpnode = node_create(tmp);
        rc = list_insert(head, tmpnode, i);
        ck_assert_int_eq(rc, 0);
    }

    int checker = 0;
    node_t *cur = *head;

    while (cur)
    {
        ck_assert_int_eq(*(int *)cur->data, checker);
        free(cur->data);
        ++checker;
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_insert_val)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    int rc = list_insert_value(head, b, 10000);
    ck_assert_int_ne(rc, 0);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        rc = list_insert_value(head, tmp, i);
        ck_assert_int_eq(rc, 0);
    }

    int checker = 0;
    node_t *cur = *head;

    while (cur)
    {
        ck_assert_int_eq(*(int *)cur->data, checker);
        free(cur->data);
        ++checker;
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_remove)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    for (size_t i = 5; i < 10; ++i)
    {
        node_t *fifth = list_remove(head, 5);
        ck_assert_int_eq(*(int *)fifth->data, i);
        ck_assert_uint_eq(list_get_length(*head), 15 - i);
        free(fifth->data);
        node_destroy(fifth);
    }

    node_t *cur = *head;

    while (cur)
    {
        free(cur->data);
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_get)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    for (size_t i = 5; i < 10; ++i)
    {
        node_t *fifth = list_get(*head, i);
        ck_assert_int_eq(*(int *)fifth->data, i);
        ck_assert_uint_eq(list_get_length(*head), 11);
    }

    node_t *cur = *head;

    while (cur)
    {
        free(cur->data);
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

void node_inc(node_t *node)
{
    (*(int *)node->data)++;
}

START_TEST(test_apply)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    list_apply(*head, node_inc);

    int checker = 1;
    node_t *cur = *head;

    while (cur)
    {
        ck_assert_int_eq(checker, *(int *)cur->data);
        ++checker;
        free(cur->data);
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

int intcmp(const void *l, const void *r)
{
    return (*(int *)l) - (*(int *)r);
}

START_TEST(test_find)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    ck_assert_ptr_eq(node_b, find(*head, a, intcmp));
    ck_assert_ptr_eq(node_e, find(*head, b, intcmp));

    node_t *cur = *head;

    while (cur)
    {
        free(cur->data);
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_pop_front)
{
    node_t **head = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 10; ++i)
    {
        int *a = calloc(1, sizeof(int));
        *a = i;
        list_unshift_value(head, a);
    }

    int ref = 9;

    while (*head)
    {
        int *first = pop_front(head);
        ck_assert_int_eq(*first, ref);
        free(first);
        ref--;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_pop_back)
{
    node_t **head = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 10; ++i)
    {
        int *a = calloc(1, sizeof(int));
        *a = i;
        list_unshift_value(head, a);
    }

    int ref = 0;

    while (*head)
    {
        int *first = pop_back(head);
        ck_assert_int_eq(*first, ref);
        free(first);
        ref++;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_insert_before)
{
    node_t **head = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    int *c = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    *c = 100;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);
    node_t *node_c = node_create(c);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    insert(head, node_c, node_b);
    ck_assert_ptr_eq(*head, node_c);
    list_shift(head);
    node_destroy(node_c);
    node_c = node_create(c);

    insert(head, node_c, node_e);
    ck_assert_ptr_eq(node_c, find(*head, c, intcmp));
    ck_assert_ptr_eq(node_c->next, node_e);

    node_t *cur = *head;

    while (cur)
    {
        free(cur->data);
        cur = cur->next;
    }

    list_destroy(head);
}
END_TEST

START_TEST(test_copy)
{
    node_t **head = calloc(1, sizeof(node_t *));
    node_t **head_cpy = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    copy(*head, head_cpy);
    ck_assert_uint_eq(list_get_length(*head), list_get_length(*head_cpy));

    node_t *cur = *head;
    node_t *cur_cpy = *head_cpy;
    while (cur)
    {
        ck_assert_ptr_eq(cur->data, cur_cpy->data);
        free(cur->data);
        cur = cur->next;
        cur_cpy = cur_cpy->next;
    }

    list_destroy(head);
    list_destroy(head_cpy);
}
END_TEST

START_TEST(test_append)
{
    node_t **head = calloc(1, sizeof(node_t *));
    node_t **head_cpy = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    for (size_t i = 11; i < 20; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_push_value(head, tmp);
    }

    append(head, head_cpy);
    ck_assert_uint_eq(list_get_length(*head), 20);
    ck_assert_uint_eq(list_get_length(*head_cpy), 0);

    int counter = 0;
    node_t *cur = *head;
    while (cur)
    {
        ck_assert_int_eq(*(int *)cur->data, counter);
        free(cur->data);
        ++counter;
        cur = cur->next;
    }

    list_destroy(head);
    list_destroy(head_cpy);
}
END_TEST

START_TEST(test_fb_split)
{
    node_t **head = calloc(1, sizeof(node_t *));
    node_t **head_cpy = calloc(1, sizeof(node_t *));

    int *a = calloc(1, sizeof(int));
    int *b = calloc(1, sizeof(int));
    *a = 0;
    *b = 10;
    node_t *node_b = node_create(a);
    node_t *node_e = node_create(b);

    list_push(head, node_b);
    list_push(head, node_e);

    for (size_t i = 1; i < 10; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_insert_value(head, tmp, i);
    }

    for (size_t i = 11; i < 20; ++i)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_push_value(head, tmp);
    }

    append(head, head_cpy);
    ck_assert_uint_eq(list_get_length(*head), 20);
    ck_assert_uint_eq(list_get_length(*head_cpy), 0);

    front_back_split(*head, head_cpy);
    ck_assert_uint_eq(list_get_length(*head), 10);
    ck_assert_uint_eq(list_get_length(*head_cpy), 10);

    int counter = 0;
    node_t *cur = *head;
    node_t *cpy_cur = *head_cpy;
    while (cur)
    {
        ck_assert_int_eq(*(int *)cur->data, counter);
        ck_assert_int_eq(*(int *)cpy_cur->data, counter + 10);
        free(cur->data);
        free(cpy_cur->data);
        ++counter;
        cur = cur->next;
        cpy_cur = cpy_cur->next;
    }

    list_destroy(head);
    list_destroy(head_cpy);
}
END_TEST

START_TEST(test_sorted_merge)
{
    node_t **head = calloc(1, sizeof(node_t *));
    node_t **head_cpy = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 20; i += 2)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_push_value(head, tmp);
    }
    for (size_t i = 1; i < 20; i += 2)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = i;
        list_push_value(head_cpy, tmp);
    }

    node_t *cur;
    node_t *new_head = sorted_merge(head, head_cpy, intcmp);
    list_destroy(head);
    list_destroy(head_cpy);

    int counter = 0;
    cur = new_head;
    while (cur)
    {
        node_t *save = cur;
        ck_assert_int_eq(*(int *)cur->data, counter);
        free(cur->data);
        ++counter;
        cur = cur->next;
        node_destroy(save);
    }
}
END_TEST

START_TEST(test_sort)
{
    node_t **head = calloc(1, sizeof(node_t *));
    node_t **head_cpy = calloc(1, sizeof(node_t *));

    for (size_t i = 0; i < 20; i += 2)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = 19 - (int)i;
        list_push_value(head, tmp);
    }
    for (size_t i = 1; i < 20; i += 2)
    {
        int *tmp = calloc(1, sizeof(int));
        *tmp = 19 - (int)i;
        list_push_value(head_cpy, tmp);
    }

    append(head, head_cpy);
    list_destroy(head_cpy);

    node_t *cur;
    node_t *new_head = sort(*head, intcmp);

    int counter = 0;
    cur = new_head;
    while (cur)
    {
        node_t *save = cur;
        ck_assert_int_eq(*(int *)cur->data, counter);
        free(cur->data);
        ++counter;
        cur = cur->next;
        node_destroy(save);
    }

    free(head);
}
END_TEST

Suite *check_my_list_suite(void)
{
    Suite *s;
    TCase *tc_node_init, *tc_length, *tc_push, *tc_push_val, *tc_pop,
    *tc_unshift, *tc_unshift_val, *tc_shift, *tc_insert, *tc_insert_val,
    *tc_remove, *tc_get, *tc_apply, *tc_find, *tc_pop_front, *tc_pop_back,
    *tc_insert_before, *tc_copy, *tc_append, *tc_fb_split, *tc_sorted_merge,
    *tc_sort;

    s = suite_create("my_list");

    {
        tc_node_init = tcase_create("node_init");
        tc_length = tcase_create("length");
        tc_push = tcase_create("push");
        tc_push_val = tcase_create("push_val");
        tc_pop = tcase_create("pop");
        tc_unshift = tcase_create("unshift");
        tc_unshift_val = tcase_create("unshift_val");
        tc_shift = tcase_create("shift");
        tc_insert = tcase_create("insert");
        tc_insert_val = tcase_create("insert_val");
        tc_remove = tcase_create("remove");
        tc_get = tcase_create("get");
        tc_apply = tcase_create("apply");
        tc_find = tcase_create("apply");
        tc_pop_front = tcase_create("pop_front");
        tc_pop_back = tcase_create("pop_back");
        tc_insert_before = tcase_create("insert_before");
        tc_copy = tcase_create("copy");
        tc_append = tcase_create("append");
        tc_fb_split = tcase_create("fb_split");
        tc_sorted_merge = tcase_create("sorted_merge");
        tc_sort = tcase_create("sort");
    }

    {
        tcase_add_test(tc_node_init, test_node_init);
        tcase_add_test(tc_length, test_length);
        tcase_add_test(tc_push, test_push);
        tcase_add_test(tc_push_val, test_push_val);
        tcase_add_test(tc_pop, test_pop);
        tcase_add_test(tc_unshift, test_unshift);
        tcase_add_test(tc_unshift_val, test_unshift_val);
        tcase_add_test(tc_shift, test_shift);
        tcase_add_test(tc_insert, test_insert);
        tcase_add_test(tc_insert_val, test_insert_val);
        tcase_add_test(tc_remove, test_remove);
        tcase_add_test(tc_get, test_get);
        tcase_add_test(tc_apply, test_apply);
        tcase_add_test(tc_find, test_find);
        tcase_add_test(tc_pop_front, test_pop_front);
        tcase_add_test(tc_pop_back, test_pop_back);
        tcase_add_test(tc_insert_before, test_insert_before);
        tcase_add_test(tc_copy, test_copy);
        tcase_add_test(tc_append, test_append);
        tcase_add_test(tc_fb_split, test_fb_split);
        tcase_add_test(tc_sorted_merge, test_sorted_merge);
        tcase_add_test(tc_sort, test_sort);
    }

    {
        suite_add_tcase(s, tc_node_init);
        suite_add_tcase(s, tc_length);
        suite_add_tcase(s, tc_push);
        suite_add_tcase(s, tc_push_val);
        suite_add_tcase(s, tc_pop);
        suite_add_tcase(s, tc_unshift);
        suite_add_tcase(s, tc_unshift_val);
        suite_add_tcase(s, tc_shift);
        suite_add_tcase(s, tc_insert);
        suite_add_tcase(s, tc_insert_val);
        suite_add_tcase(s, tc_remove);
        suite_add_tcase(s, tc_get);
        suite_add_tcase(s, tc_apply);
        suite_add_tcase(s, tc_find);
        suite_add_tcase(s, tc_pop_front);
        suite_add_tcase(s, tc_pop_back);
        suite_add_tcase(s, tc_insert_before);
        suite_add_tcase(s, tc_copy);
        suite_add_tcase(s, tc_append);
        suite_add_tcase(s, tc_fb_split);
        suite_add_tcase(s, tc_sorted_merge);
        suite_add_tcase(s, tc_sort);
    }

    return s;
}
