#!/bin/bash

if [ -f "./app.exe" ]; then
  rm app.exe
fi

if [ -f "./main.o" ]; then
  rm main.o
fi

if [ -f "./out.txt" ]; then
  rm out.txt
fi

if [ -f "./main.c.gcov" ]; then
  rm main.c.gcov
fi

if [ -f "./main.gcno" ]; then
  rm main.gcno
fi

if [ -f "./main.gcda" ]; then
  rm main.gcda
fi

exit 0
