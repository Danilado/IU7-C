#include "my_int_list.h"

node_t node_create(int data)
{
    node_t res = calloc(1, sizeof(struct int_node));
    if (!res)
        return NULL;

    res->data = data;
    res->next = NULL;

    return res;
}

void node_destroy(node_t *node)
{
    if (!node || !*node)
        return;

    free(*node);
    *node = NULL;
}

void list_clear(node_t *head)
{
    if (!head || !*head)
        return;

    node_t cur = *head;
    while (cur)
    {
        node_t next = cur->next;
        node_destroy(&cur);
        cur = next;
    }

    *head = NULL; // Оно по идее и так, но на всякий случай
}

node_t list_get_3rd_min(node_t head)
{
    if (list_get_length(head) < 3)
        return NULL;

    node_t mins[3] = {NULL, NULL, NULL};

    node_t cur = head;
    while (cur)
    {
        for (size_t i = 0; i < 3; ++i)
        {
            if (mins[i] == NULL)
            {
                mins[i] = cur;
                break;
            }
            else if (cur->data < mins[i]->data)
            {
                memmove(&mins[i + 1], &mins[i], (3 - i - 1) * sizeof(node_t));
                mins[i] = cur;
                break;
            }
        }

        cur = cur->next;
    }

    return mins[2];
}

void list_print(node_t head)
{
    if (!head)
    {
#ifdef VERBOSE
        printf("empty\n");
#endif
        return;
    }

    node_t cur = head;
    while (cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

int list_push(node_t *head, int data)
{
    if (!head)
        return -1;

    if (!*head)
    {
        *head = node_create(data);
        return (*head != NULL) ? 0 : 1;
    }

    node_t last = *head;
    while (last->next)
        last = last->next;

    node_t tmp = node_create(data);
    if (!tmp)
        return 1;

    last->next = tmp;
    return 0;
}

int list_remove(node_t *head, node_t node)
{
    if (!head)
        return -1;

    if (!*head)
        return -1;

    if (*head == node)
    {
        node_t tmp = (*head)->next;
        node_destroy(head);
        *head = tmp;
        return 0;
    }

    node_t cur = *head;
    while (cur)
    {
        if (cur->next == node)
        {
            node_t tmp = cur->next->next;
            node_destroy(&cur->next);
            cur->next = tmp;
            return 0;
        }

        cur = cur->next;
    }

    return 1;
}

size_t list_get_length(node_t head)
{
    if (!head)
        return 0;

    size_t len = 0;
    node_t cur = head;
    while (cur)
    {
        ++len;
        cur = cur->next;
    }

    return len;
}

node_t list_get_max(node_t head)
{
    if (!head)
        return NULL;

    node_t max = head;
    node_t cur = head->next;

    while (cur)
    {
        if (cur->data > max->data)
            max = cur;

        cur = cur->next;
    }

    return max;
}

int list_swap_max_2nd(node_t *head)
{
    if (list_get_length(*head) < 2)
        return -1;

    node_t max = list_get_max(*head);
    node_t second = (*head)->next;

    int tmp = max->data;
    max->data = second->data;
    second->data = tmp;

    return 0;
}
