#!/bin/bash


for FILE in *.c; do
  clang "$FILE" \
  -Wall -Werror -Wpedantic -Wextra -Wvla \
  -std=c99 -c -Og -g3 \
  -fsanitize=address -fno-omit-frame-pointer \
  -o "${FILE%.c}.o"
done

clang -lm -fsanitize=address -fno-omit-frame-pointer ./*.o -o app.exe
