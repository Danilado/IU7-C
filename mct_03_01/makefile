CC:=gcc
CFLAGS= -std=gnu99 -Wall -Werror -Wextra -Wpedantic

app.exe: main.o my_arr.o
	$(CC) -o $@ $^

main.o: main.c my_arr.h
	$(CC) $(CFLAGS) -c $<

my_arr.o: my_arr.c my_arr.h
	$(CC) $(CFLAGS) -c $<

PHONY: clean
clean:
	rm -f ./*.o ./*.exe
