#include <stdio.h>
#include <locale.h>
#include <math.h>
#define WIDTH 100
#define HEIGHT 50
typedef double (*TFunс)(double);

double funcY(double);
double funcV(double);
int printTab(TFunс, double, double, double);
int buildGraph(TFunс, double, double, double);

int main() {
	TFunс masFunc[2] = { funcY, funcV };
	int choise, opChoise;
	double x1, x2, step;

	setlocale(LC_ALL, "RUS");

	puts("Выберите функцию: ");
	puts("0) Y(x) = e ^ (cos x) * cos(sin(x))");
	puts("");
	puts("  	 |x>0.75			x+1");
	puts("1)V(x) = |0 <= x <= 0.75	1 - pow(x,5)");
	puts("         |x < 0			x + ln(|cos(x)|)");
	scanf("%d", &choise);

	puts("Выберите действие: ");
	puts("1) Вычислить значение");
	puts("2) Протабулировать функцию");
	puts("3) Построить график функции");
	scanf("%d", &opChoise);

	switch (opChoise) {
	case 1:
		printf("\nВведите x: ");
		scanf("%lf", &x1);
		printf("y = %lf\n", masFunc[choise](x1));
		break;
	case 2:
		printf("Введите диапазон и шаг через пробел: ");
		scanf("%lf %lf %lf", &x1, &x2, &step);
		printTab(masFunc[choise], x1, x2, step);
		break;
	case 3:
		printf("Введите диапазон и шаг через пробел: ");
		scanf("%lf %lf %lf", &x1, &x2, &step);
		buildGraph(masFunc[choise], x1, x2, step);
		break;
	}
}

double funcY(double x) {
	return exp(cos(x)) * cos(sin(x));
}

double funcV(double x) {
	if (x > 0.75)
		return x + 1;
	else if (x >= 0)
		return 1 - pow(x, 5);
	else
		return x + log(fabs(cos(x)));
}

int printTab(TFunс pfunc, double px1, double px2, double pstep) {
	double temp;
	printf("-----------------------------------\n");
	printf("|    x    |       f(x)            |\n");
	printf("-----------------------------------\n");
	for (double i = px1; i <= px2; i += pstep) {
		temp = pfunc(i);
		printf("| %7.3lf | %21.10lf |\n", i, temp);
	}
	return 0;
}

int buildGraph(TFunс f, double xStart, double xEnd, double step) {

	char screen[HEIGHT][WIDTH];
	double y[WIDTH];
	double ymin, ymax, hx, hy;
	int i, j, xz, yz;

	hx = (xEnd - xStart) / (WIDTH - 1);
	for (i = 0; i < WIDTH; ++i)
		y[i] = f(xStart + i * hx);

	ymin = ymax = y[0];
	for (i = 1; i < WIDTH; ++i) {
		if (y[i] < ymin) ymin = y[i];
		if (y[i] > ymax) ymax = y[i];
	}
	if (ymax == ymin) ymax = ymin + 1e-6;
	hy = (ymax - ymin) / (HEIGHT - 1);

	yz = (int)((ymax / hy) + 0.5);
	xz = (int)((0.0 - xStart) / hx + 0.5);

	for (j = 0; j < HEIGHT; ++j)
		for (i = 0; i < WIDTH; ++i)
			screen[j][i] = ' ';

	if (yz >= 0 && yz < HEIGHT)
		for (i = 0; i < WIDTH; ++i)
			screen[yz][i] = '-';

	if (xz >= 0 && xz < WIDTH)
		for (j = 0; j < HEIGHT; ++j)
			screen[j][xz] = '|';

	if (xz >= 0 && xz < WIDTH && yz >= 0 && yz < HEIGHT)
		screen[yz][xz] = '+';

	for (i = 0; i < WIDTH; ++i) {
		j = (int)((ymax - y[i]) / hy + 0.5);
		if (j >= 0 && j < HEIGHT)
			screen[j][i] = '*';
	}

	for (j = 0; j < HEIGHT; ++j) {
		for (i = 0; i < WIDTH; ++i)
			putchar(screen[j][i]);
		putchar('\n');
	}

	return 0;
}
