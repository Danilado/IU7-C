#!/bin/bash

gcc -Wall -Werror -Wpedantic -Wextra -std=c99 -c -O3 main.c
gcc -lm -o app.exe main.o
