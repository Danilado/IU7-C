#!/bin/bash

gcc main.c matrix.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3

gcc -lm main.o matrix.o -o app.exe
