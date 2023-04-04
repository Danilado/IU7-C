#!/bin/bash

gcc main.c matrixes.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3 \

gcc -lm main.o matrixes.o -o app.exe
