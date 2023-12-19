import os.path
import re
from random import randint
from typing import Literal, Optional, Union, List
import ctypes
from typing import List, Tuple
lib = ctypes.CDLL("libpymodule.so")

# int arr_fib_fill(int *dst, size_t amount);
_arr_fib_fill = lib.arr_fib_fill
_arr_fib_fill.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)
_arr_fib_fill.restype = ctypes.c_int


def arr_fib_fill(amount: int) -> Tuple[int, List[int]]:
    if amount < 0:
        print("Введённое количество элементов некорректно")
        return 1, []

    dst = (ctypes.c_int * amount)()
    rc = _arr_fib_fill(dst, amount)

    if rc != 0:
        print("Введённое количество элементов некорректно")
        return 1, []

    return rc, list(dst)


# size_t arr_unique(int *src, size_t el_count, int *dst);
_arr_unique = lib.arr_unique
_arr_unique.argtypes = (ctypes.POINTER(ctypes.c_int),
                        ctypes.c_size_t, ctypes.POINTER(ctypes.c_int))
_arr_unique.restype = ctypes.c_size_t


def arr_unique(src: list[int]) -> Tuple[int, List[int]]:
    tmpsrc = (ctypes.c_int * len(src))(*src)
    dst = (ctypes.c_int * len(src))()
    newlen = _arr_unique(tmpsrc, len(src), dst)
    return newlen, list(dst)


def main():
    arr: List[int] = []
    running = True

    while running:
        choice = input(
            "Меню:\n"
            "0: Выход\n"
            "1: Вывести список\n"
            "2: Заполнить числами Фиббоначи\n"
            "3: Вывести отфильтрованный список\n"
            "4: Добавить числа в список с клавиатуры\n"
            "> "
        )

        try:
            choice = int(choice)
        except ValueError:
            continue

        if choice == 0:
            running = False

        elif choice == 1:
            print("Список:")
            if len(arr) == 0:
                print("Список пуст")
            else:
                print(*arr, sep=" ")

        elif choice == 2:
            amount = input("Сколько чисел записать?\n> ")
            try:
                amount = int(amount)
            except ValueError:
                print("Ошибка чтения числа")
                continue
            rc, res = arr_fib_fill(amount)
            if rc != 0:
                print(
                    "Возникла ошибка: запрошенное число слишком большое\n"
                    "(в числа типа int помещается 47 чисел фиббоначи)"
                )
                continue

            arr = res

        elif choice == 3:
            size, tmp = arr_unique(arr)
            print("Результирующий список:")
            if size == 0:
                print("Список пуст")
                continue

            tmp = tmp[0:size]
            print(*tmp, sep=" ")

        elif choice == 4:
            amount = input(
                "Введите число элементов, которое хотите ввести\n> ")
            try:
                amount = int(amount)
            except ValueError:
                print("Ошибка чтения числа")
                continue

            print("Введите числа по одному:", end=" ")
            for i in range(amount):
                try:
                    num = int(input())
                except ValueError:
                    print("Ошибка чтения числа")
                    continue
                arr.append(num)

    return 0


if __name__ == '__main__':
    print("Hi!")
    main()
    print("Bye!")
