#include "student.h"

int student_input(student_s *s)
{
    fgets(s->surname, MAX_SURNAME_LEN, stdin);

    if (!strlen(s->surname))
        return BAD_SURNAME;

    if (scanf("%" PRId32, &s->height) != 1 || s->height < 0)
        return BAD_HEIGHT;

    return 0;
}

int read_student_from_file(student_s *s, FILE *f)
{
    fread(s->surname, sizeof(char), MAX_SURNAME_LEN + 1, f);
    fread(&s->height, sizeof(int), 1, f);
    return 0;
}

int print_student(student_s s)
{
    printf("Фамилия: %s Рост: %" PRId32 "\n", s.surname, s.height);
    return 0;
}
