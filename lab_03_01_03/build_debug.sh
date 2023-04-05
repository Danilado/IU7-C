#!/bin/bash

gcc main.c matrix.c array.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -Og -g3 \
-fprofile-arcs -ftest-coverage

gcc -lm -fprofile-arcs -lgcov main.o matrix.o array.o -o app.exe
