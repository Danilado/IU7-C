#!/bin/bash

gcc main.c item.c my_argparse.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -O3

gcc -lm main.o item.o my_argparse.o -o app.exe
