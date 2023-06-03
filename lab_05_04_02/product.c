#include "product.h"

int prod_comparator(product_s const *p1, product_s const *p2)
{
    if (p1->price > p2->price)
        return 0;
    if (p1->price == p2->price && p1->amount > p2->amount)
        return 0;
    return 1;
}

long filesize(FILE *f)
{
    long cur_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    long tmp = ftell(f);
    fseek(f, cur_pos, SEEK_SET);
    return tmp;
}

size_t prods_in_file(FILE *f)
{
    return filesize(f) / sizeof(product_s);
}

int get_element_by_index(FILE *f, size_t index, product_s *dst)
{
    fseek(f, sizeof(product_s) * index, SEEK_SET);
    if (fread(dst, sizeof(product_s), 1, f) != 1)
        return 1;
    return 0;
}

int put_element_by_index(FILE *f, size_t index, product_s buf)
{
    fseek(f, sizeof(product_s) * index, SEEK_SET);
    if (fwrite(&buf, sizeof(product_s), 1, f) != 1)
        return 1;
    return 0;
}

int sort_products_in_file(args_s *args)
{
    FILE *fin = fopen(args->arg1, "rb");
    if (fin == NULL)
        return BAD_FILENAME + 0;

    long fsize = filesize(fin);
    if (fsize % sizeof(product_s))
    {
        fclose(fin);
        return BAD_INPUT_FILE;
    }

    FILE *fout = fopen(args->arg2, "wb+");
    if (fout == NULL)
    {
        fclose(fin);
        return BAD_FILENAME + 1;
    }

    size_t prodcount = prods_in_file(fin);
    int rc;
    for (size_t i = 0; i < prodcount; ++i)
    {
        product_s tmpprod;
        rc = fread(&tmpprod, sizeof(tmpprod), 1, fin);
        if (rc != 1)
        {
            fclose(fin);
            fclose(fout);
            return READ_ERROR;
        }
        rc = fwrite(&tmpprod, sizeof(product_s), 1, fout);
        if (rc != 1)
        {
            fclose(fin);
            fclose(fout);
            return WRITE_ERROR;
        }
    }

    fclose(fin);
    fseek(fout, 0, SEEK_SET);

    for (size_t i = 0; i < prodcount; ++i)
        for (size_t j = 0; j < prodcount - 1 - i; ++j)
        {
            product_s tmp1, tmp2;
            rc = get_element_by_index(fout, j, &tmp1);
            rc |= get_element_by_index(fout, j + 1, &tmp2);

            if (rc)
            {
                fclose(fout);
                return READ_ERROR;
            }

            if (prod_comparator(&tmp1, &tmp2))
            {
                rc = put_element_by_index(fout, j, tmp2);
                rc |= put_element_by_index(fout, j + 1, tmp1);
            }

            if (rc)
            {
                fclose(fout);
                return WRITE_ERROR;
            }
        }

    fclose(fout);
    return 0;
}

int copy_from_end(char *restrict src, size_t len, char *restrict dst)
{
    size_t srclen = strlen(src);
    if (srclen < len)
        return 1;

    strncpy(dst, src + srclen - len, len);
    dst[len] = '\0';

    return 0;
}

int print_product(product_s *prod)
{
    int rc;
    rc = fprintf(stdout, "%s\n", prod->name);
    if (rc < 0)
        return PRINT_ERROR;
    rc = fprintf(stdout, "%s\n", prod->manufacturer);
    if (rc < 0)
        return PRINT_ERROR;
    rc = fprintf(stdout, "%" PRIu32 "\n", prod->price);
    if (rc < 0)
        return PRINT_ERROR;
    rc = fprintf(stdout, "%" PRIu32 "\n", prod->amount);
    if (rc < 0)
        return PRINT_ERROR;
    return 0;
}

int print_products_from_file(args_s *args)
{
    FILE *f = fopen(args->arg1, "rb");
    if (f == NULL)
        return BAD_FILENAME;

    int sublen = strlen(args->arg2);
    if (sublen > MAX_PRODNAME_LEN)
    {
        fclose(f);
        return SUBSTR_TOO_LONG;
    }

    long fsize = filesize(f);
    if (fsize % sizeof(product_s))
    {
        fclose(f);
        return BAD_INPUT_FILE;
    }

    size_t prodcount = prods_in_file(f);
    int prntcount = 0;

    for (size_t i = 0; i < prodcount; ++i)
    {
        product_s tmp_prod;
        int rc;
        rc = fread(&tmp_prod, sizeof(product_s), 1, f);
        if (rc != 1)
        {
            fclose(f);
            return READ_ERROR;
        }

        char substr[MAX_PRODNAME_LEN + 1];
        rc = copy_from_end(tmp_prod.name, sublen, substr);
        if (rc)
            continue;

        if (strcmp(substr, args->arg2) != 0)
            continue;

        ++prntcount;
        rc = print_product(&tmp_prod);
        if (rc)
        {
            fclose(f);
            return PRINT_ERROR;
        }
    }

    fclose(f);
    return -prntcount;
}

int scan_prodname(char name[MAX_PRODNAME_LEN + 1])
{
    char tmp_s[MAX_PRODNAME_LEN + 2];
    if (fgets(tmp_s, MAX_PRODNAME_LEN + 2, stdin) == NULL)
        return BAD_NAME;
    tmp_s[strcspn(tmp_s, "\n")] = '\0';
    if (strlen(tmp_s) >= MAX_PRODNAME_LEN + 1)
        return BAD_NAME;
    strncpy(name, tmp_s, MAX_PRODNAME_LEN + 1);
    return 0;
}

int scan_manufacter(char manufacter[MAX_MANUFACT_LEN + 1])
{
    char tmp_s[MAX_MANUFACT_LEN + 2];
    if (fgets(tmp_s, MAX_MANUFACT_LEN + 2, stdin) == NULL)
        return BAD_MANUFACTURER;
    tmp_s[strcspn(tmp_s, "\n")] = '\0';
    if (strlen(tmp_s) >= MAX_MANUFACT_LEN + 1)
        return BAD_MANUFACTURER;
    strncpy(manufacter, tmp_s, MAX_MANUFACT_LEN + 1);
    return 0;
}

int scan_product(product_s *prod)
{
    int rc = 0;
    rc = scan_prodname(prod->name);
    if (rc)
        return rc;
    rc = scan_manufacter(prod->manufacturer);
    if (rc)
        return rc;
    rc += fscanf(stdin, "%" SCNu32, &prod->price);
    rc += fscanf(stdin, "%" SCNu32, &prod->amount);
    return rc != 2;
}

int add_product_to_file(args_s *args)
{
    FILE *f = fopen(args->arg1, "rb+");
    if (f == NULL)
        return BAD_FILENAME;

    long fsize = filesize(f);
    if (fsize % sizeof(product_s))
    {
        fclose(f);
        return BAD_INPUT_FILE;
    }

    int rc;
    product_s new_prod;
    init_product(&new_prod);
    rc = scan_product(&new_prod);
    if (rc)
    {
        fclose(f);
        return BAD_PRODUCT;
    }

    long target_index = -1;
    size_t prodcount = prods_in_file(f);

    for (size_t i = 0; i < prodcount && target_index < 0; ++i)
    {
        product_s tmpprod;
        rc = get_element_by_index(f, i, &tmpprod);
        if (rc)
        {
            fclose(f);
            return READ_ERROR;
        }

        if (!prod_comparator(&new_prod, &tmpprod))
            target_index = i;
    }

    if (target_index < 0)
        target_index = prodcount;

    if (prodcount)
        for (long i = prodcount - 1; i >= target_index; --i)
        {
            product_s tmpprod;
            rc = get_element_by_index(f, i, &tmpprod);
            if (rc)
            {
                fclose(f);
                return READ_ERROR;
            }

            rc = put_element_by_index(f, i + 1, tmpprod);
            if (rc)
            {
                fclose(f);
                return WRITE_ERROR;
            }
        }

    rc = put_element_by_index(f, target_index, new_prod);
    if (rc)
    {
        fclose(f);
        return WRITE_ERROR;
    }

    fclose(f);
    return 0;
}

int init_product(product_s *prod)
{
    for (char *p = prod->name; (p - prod->name) < (long)sizeof(product_s); ++p)
        *p = '\0';

    return 0;
}
