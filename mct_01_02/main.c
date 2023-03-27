#include <stdio.h>
#include <math.h>
#include <stdio.h>

double my_cos_arcsin(double x, double eps)
{
	// a_i = (-1)**(2i - 1) * x**(i - 2) / (2 * (i + 2)! - (i + 1)!)
	// (-1)**(2i - 1) -> - всегда
	
	double sum = -x/216;
	double cur_el = sum;
	double fact = 24;
	
	for(int i = 4; fabs(cur_el) >= eps; ++i)
	{
		cur_el *= x / (2*fact*(i+1) - fact);
		sum += cur_el;
		fact *= (i+1);
	}
	
	return sum;
}

int main(void){
	double x, eps;
	double ans, perf_val;
	
	printf("Введите значение x: ");
	if(scanf("%lf", &x)!=1 || x > 1 || x < -1)
		return 1;
	
	printf("Введите значение eps: ");
	if(scanf("%lf", &eps)!=1)
		return 1;
	
	ans = my_cos_arcsin(x, eps);
	perf_val = cos(asin(x));
	
	printf("Сумма ряда: %le\n", ans);
	printf("Значение через встроенные функции: %+.5lf\n", perf_val);
	
	return 0;
}