#include "student.h"
#include "student_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BAD_MODE_INPUT 5
#define BAD_MODE 6
#define BAD_FILE_END 7
#define NOTHING_TO_OUTPUT 8

#define MAX_FILENAME_LEN 256

int main(void)
{
    int mode = 0;
    printf("Выберите режим работы\n");
    printf("1 - добавить одного\n");
    printf("2 - вывести всех\n");
    printf("3 - удалить по признаку\n");
    printf("> ");

    if (scanf("%d", &mode) != 1)
        return BAD_MODE_INPUT;
    char buf;
    scanf("%c", &buf);

    char filename[MAX_FILENAME_LEN + 1];

    printf("Введите имя файла\n> ");
    fgets(filename, MAX_FILENAME_LEN, stdin);

    int rc;
    if (mode == 1)
    {
        student_s s;
        rc = student_input(&s);
        if (rc)
            return rc;
        rc = add_student_to_file(filename, &s);
    }
    else if (mode == 2)
    {
        rc = print_students_from_file(filename);
        // моя функция возвращает кол-во выведенных элементов
        if (rc < 0)
            rc = BAD_FILE_END;
        else if (rc == 0)
            rc = NOTHING_TO_OUTPUT;
        else
            rc = 0;
    }
    else if (mode == 3)
    {
        rc = remove_students_by_attr(filename);
    }
    else
        return BAD_MODE;

    // Тут можно без if, но хочется оставить EXIT_SUCCESS
    if (rc)
        return rc;

    return EXIT_SUCCESS;
}
