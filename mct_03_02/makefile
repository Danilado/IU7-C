CC:=gcc
CFLAGS= -std=gnu99 -Wall -Werror -Wextra -Wpedantic

app.exe: main.o my_matrix.o
	$(CC) -o $@ $^

main.o: main.c my_matrix.h
	$(CC) $(CFLAGS) -c $<

my_matrix.o: my_matrix.c my_matrix.h
	$(CC) $(CFLAGS) -c $<

PHONY: clean
clean:
	rm -f ./*.o ./*.exe
