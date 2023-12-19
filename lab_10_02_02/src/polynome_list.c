#include "polynome_list.h"

#ifndef NDEBUG
#include <assert.h>
#endif

int poly_list_scanf(node_t **head)
{
    long len = 0;
    if (scanf("%ld", &len) != 1 || len < 0)
        return POLY_BAD_LEN_INPUT;

    for (size_t i = 0; i < (size_t)len; ++i)
    {
        int tmp;
        if (scanf("%d", &tmp) != 1)
        {
            list_apply(*head, pow_destroy);
            list_clear(head);
            return LIST_NO_MEMORY;
        }
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
        {
            list_apply(*head, pow_destroy);
            list_clear(head);
            return LIST_NO_MEMORY;
        }
        *tmpptr = tmp;
        list_push_value(head, tmpptr);
    }

    if (!len)
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
            return LIST_NO_MEMORY;
        *tmpptr = 0;
        list_push_value(head, tmpptr);
    }

    return EXIT_SUCCESS;
}

void pow_destroy(node_t *node)
{
    free(node->data);
}

int poly_list_get_value(const node_t *head, int var)
{
    size_t length = list_get_length(head), cur_depth = 0;
    if (!length)
        return 0;

    int sum = 0;
    const node_t *cur = head;
    while (cur)
    {
        if (cur_depth + 1 < length)
        {
            sum += *(int *)(cur->data);
            sum *= var;
        }
        else
            sum += *(int *)(cur->data);

        ++cur_depth;
        cur = cur->next;
    }

    return sum;
}

node_t *poly_list_derivative(const node_t *head)
{
    node_t **new_list = calloc(1, sizeof(node_t *));
    if (!new_list)
        return NULL;

    size_t length = list_get_length(head);

    if (length == 1)
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
            return NULL;
        *tmpptr = 0;
        list_push_value(new_list, tmpptr);
    }
    else
    {
        size_t depth = 0;
        const node_t *cur = head;

        while (cur && (depth + 1 < length))
        {
            int *tmpptr = calloc(1, sizeof(int));
            if (!tmpptr)
            {
                list_apply(*new_list, pow_destroy);
                list_clear(new_list);
                free(new_list);
                return NULL;
            }
            *tmpptr = (length - 1 - depth) * (*(int *)(cur->data));
            list_push_value(new_list, tmpptr);

            ++depth;
            cur = cur->next;
        }
    }

    node_t *res = *new_list;
    free(new_list);
    return res;
}

node_t *poly_list_sum(const node_t *head1, const node_t *head2)
{
    node_t **new_list = calloc(1, sizeof(node_t *));
    if (!new_list)
        return NULL;

    size_t len1, len2;
    len1 = list_get_length(head1);
    len2 = list_get_length(head2);

    const node_t *cur1 = head1, *cur2 = head2;

    while (len1 != len2)
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
        {
            list_apply(*new_list, pow_destroy);
            list_clear(new_list);
            free(new_list);
            return NULL;
        }
        *tmpptr = *(int *)((len1 > len2) ? (cur1->data) : (cur2->data));
        list_push_value(new_list, tmpptr);
        (len1 > len2) ? (cur1 = cur1->next) : (cur2 = cur2->next);
        (len1 > len2) ? (--len1) : (--len2);
    }

    while (cur1)
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
        {
            list_apply(*new_list, pow_destroy);
            list_clear(new_list);
            free(new_list);
            return NULL;
        }
        *tmpptr = *(int *)(cur1->data) + *(int *)(cur2->data);
        list_push_value(new_list, tmpptr);
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    node_t *res = *new_list;
    free(new_list);
    return res;
}

int poly_list_split(node_t *src_head, node_t **odd, node_t **even)
{
    if (!odd || !even)
        return LIST_NO_HEAD;

    size_t length = list_get_length(src_head);
    size_t depth = 1;

    node_t *cur = src_head;
    while (cur)
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
        {
            list_apply(*odd, pow_destroy);
            list_apply(*even, pow_destroy);
            list_clear(even);
            list_clear(odd);
            return LIST_NO_MEMORY;
        }
        *tmpptr = *(int *)(cur->data);

        if ((length - depth) % 2)
            list_push_value(odd, tmpptr);
        else
            list_push_value(even, tmpptr);

        cur = cur->next;
        ++depth;
    }

    if (!list_get_length(*odd))
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
            return LIST_NO_MEMORY;
        *tmpptr = 0;
        list_push_value(odd, tmpptr);
    }
    if (!list_get_length(*even))
    {
        int *tmpptr = calloc(1, sizeof(int));
        if (!tmpptr)
            return LIST_NO_MEMORY;
        *tmpptr = 0;
        list_push_value(even, tmpptr);
    }

    return EXIT_SUCCESS;
}

void poly_list_printf(const node_t *head)
{
    const node_t *cur = head;

    while (cur)
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    printf("L\n");
}
