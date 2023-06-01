#include "int32_file.h"

int create_file(args_s *args)
{
    FILE *f = fopen(args->filename, "wb");
    if (f == NULL)
        return BAD_FILENAME;

    srand(time(NULL));

    for (size_t i = 0; i < (size_t)args->number; ++i)
    {
        int32_t tmp = rand() % INT32_MAX;
        if (fwrite(&tmp, sizeof(int32_t), 1, f) != 1)
        {
            fclose(f);
            return i;
        }
    }

    fclose(f);
    return args->number;
}

size_t get_element_amount(FILE *f)
{
    long cur_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    fseek(f, cur_pos, SEEK_SET);
    return file_size / sizeof(int32_t);
}

int print_file(args_s *args)
{
    FILE *f = fopen(args->filename, "rb");
    if (f == NULL)
        return BAD_FILENAME;

    size_t numcount = get_element_amount(f);
    if (numcount == 0)
        return BAD_FILENAME;

    for (size_t i = 0; i < numcount; ++i)
    {
        int rc;
        int tmp;
        rc = fread(&tmp, sizeof(int32_t), 1, f);

        if (rc != 1)
            return READ_ERROR;

        printf("%" PRId32 " ", tmp);
    }
    printf("\n");

    if (feof(f))
        return READ_ERROR;

    fclose(f);
    return 0;
}

int sort_file(args_s *args)
{
    FILE *f = fopen(args->filename, "rb+");
    if (f == NULL)
        return BAD_FILENAME;
    size_t numcount = get_element_amount(f);
    fseek(f, 0, SEEK_END);
    if (ftell(f) % sizeof(int32_t))
        return READ_ERROR;

    for (size_t i = 0; i < numcount - 1; ++i)
        for (size_t j = 0; j < numcount - 1; ++j)
        {
            int rc;
            int tmp1, tmp2;
            rc = get_element_by_index(f, j, &tmp1);
            rc |= get_element_by_index(f, j + 1, &tmp2);

            if (rc)
            {
                fclose(f);
                return READ_ERROR;
            }

            if (tmp1 > tmp2)
            {
                rc = put_element_by_index(f, j, tmp2);
                rc |= put_element_by_index(f, j + 1, tmp1);
            }

            if (rc)
            {
                fclose(f);
                return WRITE_ERROR;
            }
        }

    fclose(f);
    return 0;
}

int get_element_by_index(FILE *f, size_t index, int32_t *dst)
{
    fseek(f, sizeof(int32_t) * index, SEEK_SET);
    if (fread(dst, sizeof(int32_t), 1, f) != 1)
        return 1;
    return 0;
}

int put_element_by_index(FILE *f, size_t index, int32_t buf)
{
    fseek(f, sizeof(int32_t) * index, SEEK_SET);
    if (fwrite(&buf, sizeof(int32_t), 1, f) != 1)
        return 1;
    return 0;
}
