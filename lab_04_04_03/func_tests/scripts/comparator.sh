#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ]; then
  echo Ошибка: Введите имена двух файлов в качестве первого и второго аргумента! >&2
  exit 42
fi
if [ ! -f "$1" ]; then
  if [[ "$4" == "-v" ]]; then
    echo Ошибка: файл 1 не найден!
  fi
  exit 42
fi
if [ ! -f "$2" ]; then
  if [[ "$4" == "-v" ]]; then
    echo Ошибка: файл 2 не найден!
  fi
  exit 42
fi
if [ ! -r "$1" ]; then
  if [[ "$4" == "-v" ]]; then
    echo Ошибка: недостаточно прав для доступа к файлу 1!
  fi
  exit 42
fi
if [ ! -r "$2" ]; then
  if [[ "$4" == "-v" ]]; then
    echo Ошибка: недостаточно прав для доступа к файлу 2!
  fi
  exit 42
fi

if cmp -s "$1" "$2"; then
  if [[ "$4" == "-v" ]]; then
    echo Файлы одинаковые
  fi
  exit 0
else
  if [[ "$4" == "-v" ]]; then
    echo Файлы разные
  fi
  exit 1
fi
