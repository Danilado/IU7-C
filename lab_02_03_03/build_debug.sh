#!/bin/bash

gcc main.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fprofile-arcs -ftest-coverage \
-o main.o

gcc -lm -fprofile-arcs -lgcov main.o -o app.exe
