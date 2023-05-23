#!/bin/bash

gcc main.c file.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3

gcc -lm main.o file.o -o app.exe
