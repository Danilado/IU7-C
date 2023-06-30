#!/bin/bash

./app.exe "$1" > ./out.txt

if [ ! $? ]; then
  exit 1
fi

if ./func_tests/scripts/comparator.sh ./out.txt "$2"; then
  exit 0
else
  exit 1
fi
