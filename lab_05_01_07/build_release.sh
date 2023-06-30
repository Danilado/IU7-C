#!/bin/bash

gcc main.c tuple.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3

gcc -lm main.o tuple.o -o app.exe
