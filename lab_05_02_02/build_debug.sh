#!/bin/bash

gcc main.c file.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -Og -g3 \
-fprofile-arcs -ftest-coverage

gcc -lm -fprofile-arcs -lgcov main.o file.o -o app.exe
