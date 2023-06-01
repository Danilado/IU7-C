#!/bin/bash

gcc main.c product.c my_argparse.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -O3

gcc -lm main.o product.o my_argparse.o -o app.exe
