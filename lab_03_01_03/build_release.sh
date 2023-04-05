#!/bin/bash

gcc main.c matrix.c array.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3

gcc -lm main.o matrix.o array.o -o app.exe
