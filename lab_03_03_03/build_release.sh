#!/bin/bash

gcc main.c matrixes.c arrays.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3 \

gcc -lm main.o matrixes.o arrays.o -o app.exe
