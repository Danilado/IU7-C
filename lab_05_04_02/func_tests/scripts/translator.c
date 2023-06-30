#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRODNAME_LEN 30
#define MAX_MANUFACT_LEN 15

#define PRINT_ERROR 12
#define BAD_MANUFACTURER 15
#define BAD_NAME 16

typedef struct
{
    char name[MAX_PRODNAME_LEN + 1];
    char manufacturer[MAX_MANUFACT_LEN + 1];
    uint32_t price;
    uint32_t amount;
} product_s;

int fprint_product(FILE *f, product_s *prod);

int init_product(product_s *prod)
{
    for (size_t i = 0; i < sizeof(product_s); ++i)
        prod->name[i] = '\0';

    return 0;
}

int fscan_prodname(FILE *f, char name[MAX_PRODNAME_LEN + 1])
{
    char tmp_s[MAX_PRODNAME_LEN + 2];
    if (fgets(tmp_s, MAX_PRODNAME_LEN + 2, f) == NULL)
        return BAD_NAME;
    tmp_s[strcspn(tmp_s, "\n")] = '\0';
    if (strlen(tmp_s) >= MAX_PRODNAME_LEN + 1)
        return BAD_NAME;
    strncpy(name, tmp_s, MAX_PRODNAME_LEN + 1);
    return 0;
}

int fscan_manufacter(FILE *f, char manufacter[MAX_MANUFACT_LEN + 1])
{
    char tmp_s[MAX_MANUFACT_LEN + 2];
    if (fgets(tmp_s, MAX_MANUFACT_LEN + 2, f) == NULL)
        return BAD_MANUFACTURER;
    tmp_s[strcspn(tmp_s, "\n")] = '\0';
    if (strlen(tmp_s) >= MAX_MANUFACT_LEN + 1)
        return BAD_MANUFACTURER;
    strncpy(manufacter, tmp_s, MAX_MANUFACT_LEN + 1);
    return 0;
}

int fscan_product(FILE *f, product_s *prod)
{
    int rc = 0;
    char tmpsep;
    rc = fscan_prodname(f, prod->name);
    if (rc)
        return rc;
    rc = fscan_manufacter(f, prod->manufacturer);
    if (rc)
        return rc;
    rc += fscanf(f, "%" SCNu32, &prod->price);
    rc += fscanf(f, "%" SCNu32, &prod->amount);

    fscanf(f, "%c", &tmpsep);
    return rc != 2;
}

size_t get_element_amount(FILE *f)
{
    long cur_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    fseek(f, cur_pos, SEEK_SET);
    return file_size / sizeof(int32_t);
}

void text_to_bin(char *filename1, char *filename2)
{
    FILE *f1 = fopen(filename1, "r");
    FILE *f2 = fopen(filename2, "wb");

    fseek(f1, 0, SEEK_SET);
    while (!feof(f1))
    {
        product_s tmp;
        init_product(&tmp);
        if (fscan_product(f1, &tmp))
            break;
        printf("\nnew prod\n");
        fprint_product(stdout, &tmp);
        fwrite(&tmp, sizeof(product_s), 1, f2);
    }

    fclose(f1);
    fclose(f2);
}

int fprint_product(FILE *f, product_s *prod)
{
    int rc;
    rc = fprintf(f, "%s\n", prod->name);
    if (rc < 0)
        return PRINT_ERROR;
    rc = fprintf(f, "%s\n", prod->manufacturer);
    if (rc < 0)
        return PRINT_ERROR;
    rc = fprintf(f, "%" PRIu32 "\n", prod->price);
    if (rc < 0)
        return PRINT_ERROR;
    rc = fprintf(f, "%" PRIu32 "\n", prod->amount);
    if (rc < 0)
        return PRINT_ERROR;
    return 0;
}

void bin_to_text(char *filename1, char *filename2)
{
    FILE *f1 = fopen(filename1, "rb");
    FILE *f2 = fopen(filename2, "w");

    size_t numcount = get_element_amount(f1);

    for (size_t i = 0; i < numcount; ++i)
    {
        product_s tmp;
        fread(&tmp, sizeof(product_s), 1, f1);
        fprint_product(f2, &tmp);
    }

    fclose(f1);
    fclose(f2);
}

int main(int argc, char **argv)
{
    printf("%lu", sizeof(product_s));
    if (strcmp(argv[1], "ttb") == 0)
    {
        text_to_bin(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "btt") == 0)
    {
        bin_to_text(argv[2], argv[3]);
    }
    return 0;
}
