#!/bin/bash

gcc main.c my_string.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3

gcc -lm main.o my_string.o -o app.exe
