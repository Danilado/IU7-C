#include <stdio.h>
#include <stdlib.h>

#define BAD_SURNAME 1
#define BAD_HEIGHT 2
#define BAD_INPUT_FILE 3
#define BAD_OUTPUT_FILE 4
#define BAD_MODE_INPUT 5
#define BAD_MODE 6

#define MAX_FILENAME_LEN 256
#define MAX_SURNAME_LEN 5

typedef struct student{
	char[MAX_SURNAME_LEN + 1] surname;
	int height;
} student_t;

int student_input(student_t *s)
{
	fngets(s->surname, 5);
	if (s->surname == NULL)
		return BAD_SURNAME;
	if(scanf("%d", s->height)!=1 || s->height < 0)
		return BAD_HEIGHT;
	return 0;
}

int read_student(student_t* s, FILE* in_file)
{
	fread(s->surname, sizeof(char), MAX_SURNAME_LEN+1, in_file);
	fread(s->height, sizeof(int), 1, in_file);
	return 0;
}

int print_student(student_t s)
{
	printf("Фамилия: %s Рост: %d", s.surname, s.height);
	return 0;
}

size_t print_students_from_file(FILE* in_file)
{
	size_t count = 0;
	student_t tmpstudent;
	while(feof(in_file))
	{
		read_student(&tmpstudent, in_file);
		print_student(tmpstudent);
		++count;
	}
	return count;
}

int add_student_to_file(FILE* out_file, student_t *s)
{
	fwrite(s->name, sizeof(char), MAX_SURNAME_LEN+1, out_file);
	fwrite(s->height, sizeof(int), 1, out_file);

	return 0;
}

int main(void)
{
	int mode = 0;
	printf("Введите режим работы\n");
	printf("1 - добавить одного\n");
	printf("2 - вывести всех\n");
	printf("3 - удалить по признаку\n");
	printf("4 - сортировка\n");
	printf("> ");
	
	if(scanf("%d", &mode)!=1)
		return BAD_MODE_INPUT;
	
	if(mode == 1)
	{
		char filename[MAX_FILENAME_LEN + 1];
		fngets(filename, MAX_FILENAME_LEN);
		FILE* out_file = fopen(filename, "a");
		if (out_file == NULL)
			return BAD_OUTPUT_FILE;
		student_t s;
		int rc = student_input(&s);
		if (rc)
			return rc;
		add_student_to_file(out_file, &s);
		fclose(out_file);
	}
	else if(mode == 2)
	{
		char filename[MAX_FILENAME_LEN + 1];
		fngets(filename, MAX_FILENAME_LEN);
		FILE* in_file = fopen(filename, "r");
		if (in_file == NULL)
			return BAD_INPUT_FILE;
		print_students_from_file(in_file);
		fclose(in_file);
	}
	else if(mode == 3)
	{
		
	}
	else if(mode == 4)
	{
	
	}
	else
		return BAD_MODE;
	
	return EXIT_SUCCESS;
}
