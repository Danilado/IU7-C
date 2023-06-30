#include <inttypes.h>
#include <stdio.h>
#include <string.h>

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
        int32_t tmp;
        if (fscanf(f1, "%" SCNd32, &tmp) != 1)
            break;
        fwrite(&tmp, sizeof(int32_t), 1, f2);
    }

    fclose(f1);
    fclose(f2);
}

void bin_to_text(char *filename1, char *filename2)
{
    FILE *f1 = fopen(filename1, "rb");
    FILE *f2 = fopen(filename2, "w");

    size_t numcount = get_element_amount(f1);

    for (size_t i = 0; i < numcount; ++i)
    {
        int tmp;
        fread(&tmp, sizeof(int32_t), 1, f1);
        fprintf(f2, "%" PRId32, tmp);
    }

    fclose(f1);
    fclose(f2);
}

int main(int argc, char **argv)
{
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