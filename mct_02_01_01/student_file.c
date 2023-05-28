#include "student_file.h"

size_t get_student_amount(FILE *f)
{
    int cur_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t student_count = ftell(f) / SIZEOFSTUDENT;
    fseek(f, cur_pos, SEEK_SET);
    return student_count;
}

size_t print_students_from_file(const char *filename)
{
    FILE *in_file = fopen(filename, "rb");
    if (in_file == NULL)
        return BAD_FILENAME;

    size_t studentcount;
    studentcount = get_student_amount(in_file);

    for (size_t i = 0; i < studentcount; ++i)
    {
        student_s tmpstudent;
        read_student_from_file(&tmpstudent, in_file);
        print_student(tmpstudent);
    }

    if (!feof(in_file))
    {
        fclose(in_file);
        return -1;
    }

    fclose(in_file);
    return studentcount;
}

int add_student_to_file(const char *filename, student_s *s)
{
    FILE *f = fopen(filename, "ab");
    if (f == NULL)
        return BAD_FILENAME;

    fwrite(s->surname, sizeof(char), MAX_SURNAME_LEN + 1, f);
    fwrite(&s->height, sizeof(int), 1, f);

    fclose(f);
    return 0;
}

int remove_students_by_attr(const char *filename)
{
    FILE *f = fopen(filename, "rb+");
    if (f == NULL)
        return BAD_FILENAME;

    size_t studentcount;
    studentcount = get_student_amount(f);
    double avg_height = 0.0;

    for (size_t i = 0; i < studentcount; ++i)
    {
        student_s tmpstudent;
        read_student_from_file(&tmpstudent, f);
        avg_height += tmpstudent.height;
    }
    if (!feof(f))
        return BAD_FILENAME;

    avg_height /= studentcount;

    fseek(f, 0, SEEK_SET);
    int cur_pos = 0, new_pos = 0;
    int new_studet_count = 0;

    for (size_t i = 0; i < studentcount; ++i)
    {
        student_s tmpstudent;
        read_student_from_file(&tmpstudent, f);

        cur_pos = ftell(f);
        if (tmpstudent.height > avg_height)
        {
            fseek(f, new_pos, SEEK_SET);
            new_pos = ftell(f);
            new_studet_count += 1;
            fseek(f, cur_pos, SEEK_SET);
        }
    }

    // Здесь должно быть изменение длины файла на основе переменной
    // new_student_count, но вы сказали, что мы делаем без truncate

    fclose(f);
    return 0;
}
