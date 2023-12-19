#include "item.h"

void item_print(item_t *item)
{
    printf("%s\n", item->name);
    printf("%.6lf\n", item->weight);
    printf("%.6lf\n", item->volume);
    return;
}

int item_name_scan(limited_string dst, FILE *stream)
{
    char tmp_string[MAX_ITEM_NAME_LEN + 2];

    if (fgets(tmp_string, MAX_ITEM_NAME_LEN + 2, stream) == NULL)
        return BAD_NAME;

    tmp_string[strcspn(tmp_string, "\n")] = '\0';

    if (strlen(tmp_string) == 0)
        return NO_NAME;

    if (strlen(tmp_string) && (strlen(tmp_string) > MAX_ITEM_NAME_LEN))
        return TOO_LONG_NAME;

    strncpy(dst, tmp_string, MAX_ITEM_NAME_LEN + 1);

    return 0;
}

int item_scan(item_t *item, FILE *stream)
{
    int rc = item_name_scan(item->name, stream);

    if (rc)
        return rc;

    if (fscanf(stream, "%lf\n", &item->weight) != 1)
        return NO_WEIGHT;

    if (item->weight <= EPS)
        return BAD_WEIGHT;

    if (fscanf(stream, "%lf\n", &item->volume) != 1)
        return NO_VOLUME;

    if (item->volume <= EPS)
        return BAD_VOLUME;

    return 0;
}

int item_arr_scan(item_arr_t dst, size_t *len, FILE *stream)
{
    size_t length = 0;
    while (!feof(stream))
    {
        if (length >= MAX_ITEM_COUNT)
            return TOO_MANY_ITEMS;

        item_t buf;
        int rc;
        rc = item_scan(&buf, stream);
        if (rc)
        {
            if (rc == NO_NAME && length != 0 && feof(stream))
                break;
            return rc;
        }

        dst[length] = buf;
        ++length;
    }

    *len = length;
    return 0;
}

size_t pref_items_print(item_arr_t src, size_t items_len, char *prefix)
{
    size_t printed_count = 0;

    for (size_t i = 0; i < items_len; ++i)
        if (strlen(prefix) == 0 ||
            strncmp(src[i].name, prefix, strlen(prefix)) == 0)
        {
            item_print(&src[i]);
            ++printed_count;
        }

    return printed_count;
}

// should be stable when going left to right
bool density_comparator(item_t *i1, item_t *i2)
{
    double d1, d2;
    d1 = i1->weight / i1->volume;
    d2 = i2->weight / i2->volume;
    if (d2 > d1 || fabs(d2 - d1) < EPS)
        return false;
    return true;
}

void sort_by_density(item_arr_t arr, size_t alen)
{
    for (size_t i = 1; i < alen; ++i)
        for (size_t j = 1; j < alen - i + 1; ++j)
            if (density_comparator(&arr[j - 1], &arr[j]))
            {
                item_t buf = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = buf;
            }

    return;
}
