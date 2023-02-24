#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ]; then
  echo Ошибка: Введите имена двух файлов в качестве первого и второго аргумента! >&2
  exit 42
fi
if [ ! -f "$1" ]; then
  if [[ "$3" == "-v" ]]; then
    echo Ошибка: файл 1 не найден!
  fi
  exit 42
fi
if [ ! -f "$2" ]; then
  if [[ "$3" == "-v" ]]; then
    echo Ошибка: файл 2 не найден!
  fi
  exit 42
fi
if [ ! -r "$1" ]; then
  if [[ "$3" == "-v" ]]; then
    echo Ошибка: недостаточно прав для доступа к файлу 1!
  fi
  exit 42
fi
if [ ! -r "$2" ]; then
  if [[ "$3" == "-v" ]]; then
    echo Ошибка: недостаточно прав для доступа к файлу 2!
  fi
  exit 42
fi

tmp1=$(mktemp)
FLAG=""

FIN=false
until $FIN; do
  read -r line || FIN=true
  for word in $line; do
    if [[ "$word" =~ ^[+-]?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?$ ]]; then
      FLAG="true"
      echo "$word" >> "$tmp1"
    fi
  done
done <"$1"

if [ -z "$FLAG" ]; then
  if [[ "$3" == "-v" ]]; then
    echo Ошибка: В файле 1 нет ЧПТ!
  fi
  
  exit 42
fi

tmp2=$(mktemp)
FLAG=""

FIN=false
until $FIN; do
  read -r line || FIN=true
  for word in $line; do
    if [[ "$word" =~ ^[+-]?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?$ ]]; then
      FLAG="true"
      echo "$word" >> "$tmp2"
    fi
  done
done <"$2"

if [ -z "$FLAG" ]; then
  if [[ "$3" == "-v" ]]; then
    echo Ошибка: В файле 2 нет ЧПТ!
  fi
  
  exit 42
fi



if cmp -s "$tmp1" "$tmp2"; then
  if [[ "$3" == "-v" ]]; then
    echo Файлы одинаковые
  fi
  exit 0
else
  if [[ "$3" == "-v" ]]; then
    echo Файлы разные
  fi
  exit 1
fi
