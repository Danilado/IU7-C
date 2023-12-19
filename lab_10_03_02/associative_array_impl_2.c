#include "associative_array.h"
#include "my_list.h"

struct assoc_array_type
{
    node_t **content;
};

typedef struct dict_key *dict_key_t;
struct dict_key
{
    const char *key;
    int value;
};

dict_key_t key_init(const char *key, int value)
{
    if (strlen(key) == 0)
        return NULL;

    dict_key_t res = calloc(1, sizeof(struct dict_key));
    if (!res)
        return NULL;

    res->key = key;
    res->value = value;

    return res;
}

const char *key_get_keyptr(dict_key_t key)
{
    if (!key)
        return NULL;
    return key->key;
}

int key_get_val(dict_key_t key)
{
    if (!key)
        return 0;
    return key->value;
}

void key_destroy(dict_key_t key)
{
    free(key);
}

assoc_array_t assoc_array_create(void)
{
    assoc_array_t res = calloc(1, sizeof(struct assoc_array_type));
    if (!res)
        return NULL;

    res->content = calloc(1, sizeof(node_t *));
    if (!res->content)
    {
        free(res);
        return NULL;
    }

    return res;
}

void key_destroyer(node_t *node)
{
    dict_key_t tmp = node->data;
    key_destroy(tmp);
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr)
        return;

    if (!*arr)
        return;

    if ((*arr)->content)
    {
        list_apply(*(*arr)->content, key_destroyer);
        list_destroy((*arr)->content);
    }

    free(*arr);

    *arr = NULL;
}

// clang-format off
assoc_array_error_t assoc_array_insert(assoc_array_t arr, 
const char *key, int num)
{
    // clang-format on
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < list_get_length(*(arr->content)); ++i)
    {
        node_t *tmpnode = list_get(*(arr->content), i);
        dict_key_t tmp = tmpnode->data;
        if (strcmp(tmp->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;
    }

    dict_key_t element = key_init(key, num);
    if (!element)
        return ASSOC_ARRAY_MEM;

    int rc = list_push_value(arr->content, element);
    if (rc)
        return ASSOC_ARRAY_MEM;

    return ASSOC_ARRAY_OK;
}

// clang-format off
assoc_array_error_t assoc_array_find(const assoc_array_t arr, 
const char *key, int **num)
{
    // clang-format on
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < list_get_length(*(arr->content)); ++i)
    {
        node_t *tmpnode = list_get(*(arr->content), i);
        dict_key_t tmp = tmpnode->data;
        if (strcmp(tmp->key, key) == 0)
        {
            *num = &tmp->value;
            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!key)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < list_get_length(*(arr->content)); ++i)
    {
        node_t *tmpnode = list_get(*(arr->content), i);
        dict_key_t tmp = tmpnode->data;
        if (strcmp(tmp->key, key) == 0)
        {
            node_t *resnode = list_remove(arr->content, i);
            dict_key_t res = resnode->data;
            node_destroy(resnode);
            key_destroy(res);
            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    list_apply(*(arr->content), key_destroyer);
    list_clear(arr->content);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr,
void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < list_get_length(*(arr->content)); ++i)
    {
        node_t *tmpnode = list_get(*(arr->content), i);
        dict_key_t tmp = tmpnode->data;
        action(tmp->key, &tmp->value, param);
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (list_get_length(*(arr->content)) == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    dict_key_t min;

    {
        node_t *tmpnode = list_get(*(arr->content), 0);
        min = tmpnode->data;
    }

    for (size_t i = 1; i < list_get_length(*(arr->content)); ++i)
    {
        node_t *tmpnode = list_get(*(arr->content), i);
        dict_key_t tmp = tmpnode->data;
        if (strcmp(min->key, tmp->key) > 0)
            min = tmp;
    }

    *num = &min->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (list_get_length(*(arr->content)) == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    dict_key_t max;

    {
        node_t *tmpnode = list_get(*(arr->content), 0);
        max = tmpnode->data;
    }

    for (size_t i = 1; i < list_get_length(*(arr->content)); ++i)
    {
        node_t *tmpnode = list_get(*(arr->content), i);
        dict_key_t tmp = tmpnode->data;
        if (strcmp(max->key, tmp->key) < 0)
            max = tmp;
    }

    *num = &max->value;
    return ASSOC_ARRAY_OK;
}
