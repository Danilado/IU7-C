#!/bin/bash

gcc main.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -O3 \
-o main.o

gcc -lm main.o -o app.exe
