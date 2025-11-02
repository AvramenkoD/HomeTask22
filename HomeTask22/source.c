/*Y(x) = e ^ (cos x) * cos(sin(x))
	   x>0.75			x+1
V(x) = 0 <= x <= 0.75	1 - pow(x,5)
	   x < 0			x + ln(|cos(x)|)
*/
#include <stdio.h>
#include <locale.h>
#include <math.h>

typedef double (*TFun)(double);

double funcY(double);
double funcV(double);
int printTab(TFun, double, double, double);

int main() {

	int choise;
	double x1, x2, step;

	setlocale(LC_ALL, "RUS");

	printf("Введите диапозон и шаг через пробел: ");
	scanf("%lf %lf %lf", &x1, &x2, &step);

	puts("Выберите функцию: ");
	puts("1) Y(x) = e ^ (cos x) * cos(sin(x))");
	puts("");
	puts("  	 |x>0.75			x+1");
	puts("2)V(x) = |0 <= x <= 0.75	1 - pow(x,5)");
	puts("         |x < 0			x + ln(|cos(x)|)");
	scanf("%d", &choise);

	if (choise = 1)
		printTab(funcY, x1, x2, step);
	else
		printTab(funcV, x1, x2, step);
}
double funcY(double x) {
	double rez = exp(cos(x)) * cos(sin(x));
	return rez;
}
double funcV(double x) {
	double rez = 0;
	if (x > 0.75)
		rez = x + 1;
	else if (x >= 0)
		rez = 1 - pow(x, 5);
	else
		rez = x + log(fabs(cos(x)));
	return rez;
}

int printTab(TFun pfunc, double px1, double px2,double pstep) {

	double temp;

	printf("-----------------------------------\n");
	printf("|    x    |       f(x)            |\n");
	printf("-----------------------------------\n");
	
	for (double i = px1; i <= px2; i += pstep) {
		temp = pfunc(i);
		printf("| %7lf | %21lf |\n", i, temp);
	}
	return 0;
}