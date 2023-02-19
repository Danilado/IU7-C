#!/bin/bash

gcc -Wall -Werror -Wpedantic -Wextra -std=c99 -c -O1 main.c
gcc -lm -o app.exe main.o
