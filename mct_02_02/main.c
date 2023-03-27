#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NMAX 1024
/*
Реализовать функцию, которая ставит на место после каждого двузначного числа определённое число. 
Принять с клавиатуры число, принять с клавиатуры массив не более, чем из 1024 элементов, применить к нему первую и вторую функции и вывести результат на экран. 
К каждой функции указать описание в любом удобном формате.
*/

typedef arr_t int[NMAX];

bool is_full_square(int n)
{
	return (sqrt((double)n) - (int)sqrt((double)n)) <= 1e-8;
}

bool is_two_digit(int n)
{
	return n/100 == 0 && n/10 > 0;	
}

/*
Функция-фильтр принимающая в себя исходный массив - src
и выходной - dst
а также длину исходного массива - srclen формата size_t
возвращает длину выходного массива и изменяет
выходной массив в процессе выполнения оставляя
в нём только полные квадраты из исходного
MEMORY OVERLAP - UNDEFINED BEHAVIOUR
*/
size_t filter_squares(arr_t src, arr_t dst, size_t srclen)
{
	size_t dstlen = 0;
	for(size_t i = 0; i<srclen; ++i)
		if (is_full_square(arr[i]))
		{
			dst[dstlen] = arr[i];
			++dstlen;
		}	
	
	return dstlen;
}

/*
Функция принимающая в себя исходный массив - src
и выходной - dst
а также длину исходного массива - srclen формата size_t
возвращает длину выходного массива и вносит в выходной
массив копию входного с добавление числа переданного
в качестве 4 аргумента после каждого двузначного числа
MEMORY OVERLAP - UNDEFINED BEHAVIOUR
*/
size_t put_additional_number(arr_t src, arr_t dst, size_t srclen, int num)
{
	size_t dstlen = 0;
	for(size_t i = 0; i<srclen; ++i)
	{
		if (is_two_digit(arr[i]))
		{
			dst[dstlen] = arr[i];
			dst[dstlen+1] = num;
			dstlen += 2;
		}
		else
		{
			dst[dstlen] = arr[i];
			dstlen++;
		}
	}
	
	return dstlen;
}


int main(void)
{
	size_t alen;
	arr a;
	
	scanf("%zu", &alen);
	
	for(size_t i = 0; i<alen; ++i)
		scanf("%d", &a[i]);
	
}