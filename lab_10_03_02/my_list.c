#include "my_list.h"

#ifndef NDEBUG
#include <assert.h>
#endif

node_t *node_create(void *data)
{
    node_t *res = calloc(1, sizeof(struct node));
    if (!res)
        return NULL;

    res->next = NULL;
    res->data = data;
    return res;
}

void list_destroy(node_t **head)
{
    if (!head)
        return;
    node_t *cur = *head;
    while (cur)
    {
        node_t *next = cur->next;
        node_destroy(cur);
        cur = next;
    }

    free(head);
}

void list_clear(node_t **head)
{
    if (!head || !*head)
        return;

    node_t *cur = *head;
    while (cur)
    {
        node_t *next = cur->next;
        node_destroy(cur);
        cur = next;
    }

    *head = NULL;
}

void node_destroy(node_t *node)
{
    free(node);
}

void *node_get_data(node_t *node)
{
    return node->data;
}

size_t list_get_length(const node_t *head)
{
    if (!head)
        return 0;
    size_t length = 1;
    const node_t *cur = head;

    while (cur->next)
    {
        ++length;
        cur = cur->next;
    }

    return length;
}

void list_push(node_t **head, node_t *node)
{
#ifndef NDEBUG
    assert(node != NULL);
#endif
    node->next = NULL;

    if (!*head)
        *head = node;
    else
    {
        node_t *tail = *head;
        while (tail->next)
            tail = tail->next;

        tail->next = node;
    }
}

int list_push_value(node_t **head, void *value)
{
    node_t *node = node_create(value);
    if (!node)
        return LIST_NO_MEMORY;

    list_push(head, node);
    return EXIT_SUCCESS;
}

void list_unshift(node_t **head, node_t *node)
{
#ifndef NDEBUG
    assert(node != NULL);
#endif
    node->next = *head;
    *head = node;
}

int list_unshift_value(node_t **head, void *value)
{
    node_t *node = node_create(value);
    if (!node)
        return LIST_NO_MEMORY;

    list_unshift(head, node);
    return EXIT_SUCCESS;
}

int list_insert(node_t **head, node_t *node, size_t index)
{
#ifndef NDEBUG
    assert(node != NULL);
#endif

    size_t length = list_get_length(*head);

    if (index > length)
        return LIST_BAD_INDEX;

    if (!index)
    {
        list_unshift(head, node);
        return EXIT_SUCCESS;
    }

    if (index == length)
    {
        list_push(head, node);
        return EXIT_SUCCESS;
    }

    node_t *target = *head;
    for (size_t i = 0; i < index - 1; ++i)
        target = target->next;

    node->next = target->next;
    target->next = node;

    return EXIT_SUCCESS;
}

int list_insert_value(node_t **head, void *value, size_t index)
{
    if (index > list_get_length(*head))
        return LIST_BAD_INDEX;

    node_t *node = node_create(value);
    if (!node)
        return LIST_NO_MEMORY;

    return list_insert(head, node, index);
}

node_t *list_pop(node_t **head)
{
    size_t length = list_get_length(*head);

    if (!length)
        return NULL;
    if (length == 1)
    {
        node_t *res = *head;
        *head = NULL;
        return res;
    }

    node_t *prev = *head;
    node_t *cur = prev->next;

    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
    }

    prev->next = NULL;
    return cur;
}

node_t *list_shift(node_t **head)
{
    if (!list_get_length(*head))
        return NULL;

    node_t *res = *head;
    *head = (*head)->next;
    return res;
}

// изначально было remove_by_index, но это очень длинно
node_t *list_remove(node_t **head, size_t index)
{
    size_t length = list_get_length(*head);
    if (index >= length)
        return NULL;

    if (!index)
        return list_shift(head);
    if (index == length - 1)
        return list_pop(head);

    node_t *pre_target = *head;
    for (size_t i = 0; i < index - 1; ++i)
        pre_target = pre_target->next;

    node_t *res = pre_target->next;
    pre_target->next = res->next;
    return res;
}

// изначально было get_by_index, но это очень длинно
node_t *list_get(const node_t *head, size_t index)
{
    size_t length = list_get_length(head);
    if (index >= length)
        return NULL;

    const node_t *target = head;
    for (size_t i = 0; i < index; ++i)
        target = target->next;

    return (node_t *)target;
}

// ***

void list_apply(node_t *head, void (*func)(node_t *))
{
    node_t *cur = head;
    while (cur)
    {
        func(cur);
        cur = cur->next;
    }
}

// ЗАДАНИЯ ПО ВЫБОРУ

// clang-format off
node_t *find(node_t *head, const void *data, 
int (*comparator)(const void *, const void *))
{
    // clang-format on
    node_t *cur = head;
    while (cur)
    {
        if (comparator(cur->data, data) == 0)
            return cur;
        cur = cur->next;
    }

    return NULL;
}

void *pop_front(node_t **head)
{
    if (!head || !*head)
        return NULL;

    node_t *node = list_shift(head);
    if (!node)
        return NULL;

    void *res = node->data;
    node_destroy(node);
    return res;
}

void *pop_back(node_t **head)
{
    if (!head || !*head)
        return NULL;

    node_t *node = list_pop(head);
    if (!node)
        return NULL;

    void *res = node->data;
    node_destroy(node);
    return res;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == NULL && before == NULL)
    {
        elem->next = before;
        *head = elem;
        return;
    }

    if (!*head || !before)
        return;

    if (*head == before)
    {
        list_unshift(head, elem);
        return;
    }

    node_t *target = *head;
    for (size_t i = 0; i < list_get_length(*head); ++i)
    {
        if (target->next == before)
            break;
        target = target->next;
    }

    if (target && target->next == before)
    {
        elem->next = before;
        target->next = elem;
    }
}

int copy(node_t *head, node_t **new_head)
{
#ifndef NDEBUG
    assert(new_head != NULL);
#endif

    if (list_get_length(*new_head))
        list_clear(new_head);

    if (!head)
    {
        *new_head = head;
        return LIST_NO_HEAD;
    }

    node_t *cur = head;
    while (cur)
    {
        // данные не копируются, но создаются новые узлы
        int rc = list_push_value(new_head, cur->data);
        if (rc)
        {
            list_destroy(new_head);
            return rc;
        }
        cur = cur->next;
    }

    return EXIT_SUCCESS;
}

void append(node_t **head_a, node_t **head_b)
{
    if (!*head_a)
    {
        *head_a = *head_b;
        *head_b = NULL;
        return;
    }

    node_t *a_end = *head_a;
    while (a_end->next)
        a_end = a_end->next;

    a_end->next = *head_b;
    *head_b = NULL;
}

void front_back_split(node_t *head, node_t **back)
{
    if (!head)
        return;

    size_t flen = list_get_length(head);

    if (flen == 1)
        return;

    size_t newflen = flen / 2 + flen % 2;
    node_t *middle = head;
    for (size_t i = 0; i < newflen - 1; ++i)
        middle = middle->next;

    *back = middle->next;
    middle->next = NULL;
}

// clang-format off
node_t *sorted_merge(node_t **head_a, node_t **head_b, 
int (*comparator)(const void *, const void *))
{
    // clang-format on
    node_t **res = calloc(1, sizeof(node_t *));
#ifndef NDEBUG
    assert(res != NULL);
#endif
    if (!res)
        return NULL;

    while (*head_a || *head_b)
    {
        if (!*head_a)
        {
            append(res, head_b);
            break;
        }
        if (!*head_b)
        {
            append(res, head_a);
            break;
        }

        if (comparator((*head_a)->data, (*head_b)->data) <= 0)
            list_push(res, list_shift(head_a));
        else
            list_push(res, list_shift(head_b));
    }

    // list_destroy(head_a);
    // list_destroy(head_b);

    node_t *fin = *res;
    free(res);
    return fin;
}

node_t *merge_sort(node_t **head, int (*comparator)(const void *, const void *))
{
#ifndef NDEBUG
    assert(*head != NULL);
#endif

    size_t length = list_get_length(*head);
    if (length <= 1)
        return *head;
    if (length == 2)
    {
        if (comparator((*head)->data, (*head)->next->data) > 0)
        {
            void *tmp = (*head)->data;
            (*head)->data = (*head)->next->data;
            (*head)->next->data = tmp;
        }
        return *head;
    }

    node_t **tmp = calloc(1, sizeof(node_t *));
#ifndef NDEBUG
    assert(tmp != NULL);
#endif
    front_back_split(*head, tmp);

    // для совпадения типов
    // clang-format off
    node_t **tmp1 = calloc(1, sizeof(node_t *)),
    **tmp2 = calloc(1, sizeof(node_t *));
    // clang-format on
    *tmp1 = merge_sort(head, comparator);
    *tmp2 = merge_sort(tmp, comparator);

    node_t *res = sorted_merge(tmp1, tmp2, comparator);
    free(tmp);
    list_destroy(tmp1);
    list_destroy(tmp2);
    return res;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (!head)
        return head;

    return merge_sort(&head, comparator);
}
