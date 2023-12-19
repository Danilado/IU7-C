#include "item.h"

struct item_type_t
{
    char *name;
    double weight;
    double volume;
};

item_t item_create(void)
{
    item_t res = calloc(1, sizeof(struct item_type_t));
    if (!res)
        return NULL;

    res->name = NULL;
    res->weight = 1.0;
    res->volume = 1.0;

    return res;
}

char *item_get_name(const item_t item)
{
    return item->name;
}
double item_get_weight(const item_t item)
{
    return item->weight;
}
double item_get_volume(const item_t item)
{
    return item->volume;
}

void item_set_name(item_t item, char *name)
{
    item->name = name;
}
void item_set_weight(item_t item, double weight)
{
    item->weight = weight;
}
void item_set_volume(item_t item, double volume)
{
    item->volume = volume;
}

double item_get_density(const item_t item)
{
    return item->weight / item->volume;
}

void item_destroy(item_t item)
{
    free(item->name);
    free(item);
}

void item_print(item_t item)
{
    printf("%s\n", item->name);
    printf("%.6lf\n", item->weight);
    printf("%.6lf\n", item->volume);
}

char *item_name_scan(FILE *stream)
{
    size_t buflen = NAME_START_LEN + 1;
    char *buf = calloc(buflen, sizeof(char));

    ssize_t rc = getline(&buf, &buflen, stream);
    if (rc < 0)
    {
        free(buf);
        return NULL;
    }

    // Если считано только \n
    if (rc == 1)
    {
        free(buf);
        return NULL;
    }

    buf[strcspn(buf, "\n")] = '\0';

    return buf;
}

int item_scanf(item_t item, FILE *stream)
{
    item->name = item_name_scan(stream);
    if (!item->name)
        return NO_NAME;

    if (fscanf(stream, "%lf\n", &item->weight) != 1)
    {
        free(item->name);
        item->name = NULL;
        return NO_WEIGHT;
    }

    if (item->weight <= EPS)
    {
        free(item->name);
        item->name = NULL;
        return BAD_WEIGHT;
    }

    if (fscanf(stream, "%lf\n", &item->volume) != 1)
    {
        free(item->name);
        item->name = NULL;
        return NO_VOLUME;
    }

    if (item->volume <= EPS)
    {
        free(item->name);
        item->name = NULL;
        return BAD_VOLUME;
    }

    return 0;
}

int density_comparator(const void *vi1, const void *vi2)
{
    const item_t i1 = (void *)vi1;
    const item_t i2 = (void *)vi2;
    double d1, d2;
    d1 = item_get_density(i1);
    d2 = item_get_density(i2);

    if (fabs(d2 - d1) < EPS)
        return 0;

    if (d2 - d1 > 0)
        return -1;

    return 1;
}
