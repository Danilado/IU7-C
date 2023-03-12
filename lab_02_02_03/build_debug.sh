#!/bin/bash

gcc -Wall -Werror -Wpedantic -Wextra -std=c99 -c -fprofile-arcs -ftest-coverage -Og -g3 main.c
gcc -lm -fprofile-arcs -lgcov main.o -o app.exe
