#include "dynarr.h"

int dyn_arr_init(size_t el_size, size_t el_count, my_dyn_arr_t *dst)
{
    void *ptr = calloc(el_count, el_size);
    if (ptr == NULL)
        return NOT_ENOUGH_MEMORY;

    dst->pb = ptr;
    dst->pe = (char *)ptr + el_size * el_count;
    dst->el_size = el_size;

    return EXIT_SUCCESS;
}

void dyn_arr_destroy(my_dyn_arr_t *arr)
{
    free(arr->pb);
    arr->pb = NULL;
    arr->pe = NULL;
    arr->el_size = 0;
}

// unit tested
int swap(void *pl, void *pr, size_t size)
{
    char buf[size];

    memcpy(buf, pl, size);
    memcpy(pl, pr, size);
    memcpy(pr, buf, size);

    return EXIT_SUCCESS;
}

// unit tested
// clang-format off
void mysort(
    void *base, size_t num, size_t size, 
int (*compare)(const void *, const void *))
{
    // clang-format on
    void *buf = calloc(1, size);

    if (buf == NULL)
        return;

    char *cbase = (char *)base;

    for (size_t i = 0; i < num; ++i)
    {
        memcpy(buf, base, size);
        size_t max_offset = 0;

        for (char *pcur = cbase; (pcur - cbase) / size < num - i; pcur += size)
            if (compare(pcur, buf) > 0)
            {
                max_offset = (pcur - cbase);
                memcpy(buf, pcur, size);
            }

        swap(cbase + size * (num - i - 1), cbase + max_offset, size);
    }

    free(buf);
}

// unit tested
int int_cmp(const void *pl, const void *pr)
{
    int *pil = (int *)pl;
    int *pir = (int *)pr;

    return *pil - *pir;
}

int count_numbers_in_file(FILE *file, size_t *dst)
{
    NUM_TYPE tmp;
    int rc;

    *dst = 0;

    while ((rc = fscanf(file, "%" SCN_FORMAT, &tmp)) == 1)
        ++*dst;

    fseek(file, 0, SEEK_SET);

    if (rc != EOF)
        return FSCANF_ERROR;
    if (*dst == 0)
        return NO_ELEMENTS;

    return EXIT_SUCCESS;
}

int fill_dyn_arr_from_file(my_dyn_arr_t *dst, FILE *file)
{
    NUM_TYPE *pb = (NUM_TYPE *)dst->pb;

    for (NUM_TYPE *pcur = pb; pcur < (NUM_TYPE *)dst->pe; ++pcur)
        fscanf(file, "%" SCN_FORMAT, pcur);

    fseek(file, 0, SEEK_SET);

    return EXIT_SUCCESS;
}

int fprint_dyn_arr(my_dyn_arr_t *src, FILE *file)
{
    if (((char *)src->pe - (char *)src->pb) == 0)
        return NOTHING_TO_OUTPUT;

    NUM_TYPE *pb = (NUM_TYPE *)src->pb;

    for (NUM_TYPE *pcur = pb; pcur < (NUM_TYPE *)src->pe; ++pcur)
        if (fprintf(file, "%" PRI_FORMAT " ", *pcur) < 0)
            return FPRINTF_ERROR;

    return EXIT_SUCCESS;
}

// unit tested
int key(const NUM_TYPE *pb_src, const NUM_TYPE *pe_src, NUM_TYPE **pb_dst,
NUM_TYPE **pe_dst)
{
    if (pe_src < pb_src)
        return BAD_SRC_PTRS;

    if (!pb_dst || !*pb_dst || !pe_dst || !*pe_dst)
        return BAD_DST_PTRS;

    size_t last_neg_index = pe_src - pb_src;

    for (NUM_TYPE *pcur = (NUM_TYPE *)pb_src; pcur < pe_src; ++pcur)
        if (*pcur < 0)
            last_neg_index = pcur - pb_src;

    if (!last_neg_index)
        return EMPTY_ARRAY;

    if ((size_t)(*pe_dst - *pb_dst) < last_neg_index)
        return NO_MEMORY;

    *pe_dst = *pb_dst + last_neg_index;

    memcpy(*pb_dst, pb_src, (*pe_dst - *pb_dst) * sizeof(NUM_TYPE));

    return EXIT_SUCCESS;
}
