# Задание к работе 22

## Условие задачи
Разработайте программу табуляции трех заданных функций, состоящую из трех отдельных математических функций и функции печати таблицы значений, которая принимает в качестве параметра - указатель на выбранную математическую функцию.
Дополните программу меню, позволяющее выбирать функции и действия с ними(построить график выбранной функции).
Реализовать функцию calculate (TFun prtf, double *x, int n), которая по
заданной указателем prtf функции для значений массива х, размера n:
(Вычисляет сумму максимального и минимального значений функции)
---
## 1. Алгоритм и блок схема

### Алгоритм
1. **Начало**
2. Объявляем макросы и новый тип данных.
3. Объявляем прототипы функций.
4. Объявляем переменные.
5. Запрашиваем у пользователя функцию, действие и данные для действия над ней.
   а. Вычисление значения функции по x
   б. Табуляция функции по диапозону и шагу (вычисляем значения и подставляем в таблицу)
   в. Построить график функции
   		Создаём двумерный массив символов
   		Заполняем * в точки с координатами (x,f(x)) остальное пробеламии осями координат
   		Печатаем
7. **Конец**

### Блок-схема
![Блок-схема алгоритма](Lab22_schema.jpg)

 [Ссылка на блок-схему](https://viewer.diagrams.net/?tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Lab10.1_schema.drawio&dark=auto#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1JpmhIfzJodOCcWVEdJUO9KuQrloiS01t%26export%3Ddownload)

 ## 2. Реализация программы

```c
﻿#include <stdio.h>
#include <locale.h>
#include <math.h>
#define WIDTH 100
#define HEIGHT 50
#define SIZE1 10
typedef double (*TFunс)(double);

double funcY(double);
double funcV(double);
double calculate(TFunс, double*, int);
int printTab(TFunс, double, double, double);
int buildGraph(TFunс, double, double, double);

int main() {

	TFunс masFunc[2] = { funcY, funcV };
	double masX[SIZE1];
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
	puts("4) Вычислить сумму максимального и минимального значений функции");
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
		case 4:
			printf("Введите %d значений x через Enter: ",SIZE1);
			for (int i = 0; i < SIZE1; i++) {
				scanf("%lf", &masX[i]);
			}
			printf("Сумма макс и мин значений = %lf", calculate(masFunc[choise], masX, SIZE1));
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
	char screen[WIDTH][HEIGHT];
	double x, y[WIDTH];
	double ymin = 0, ymax = 0;
	double hx, hy;
	int i, j;
	int xz, yz;

	hx = (xEnd - xStart) / (WIDTH - 1);

	for (i = 0, x = xStart; i < WIDTH; ++i, x += hx) {

		y[i] = f(x);
		if (y[i] < ymin)
			ymin = y[i];
		if (y[i] > ymax)
			ymax = y[i];
	}

	hy = (ymax - ymin) / (HEIGHT - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - xStart) / hx + 0.5);


	for (j = 0; j < HEIGHT; ++j) {
		for (i = 0; i < WIDTH; ++i) {

			if (j == yz && i == xz)
				screen[i][j] = '+';
			else if (j == yz)
				screen[i][j] = '-';
			else if (i == xz)
				screen[i][j] = '|';
			else
				screen[i][j] = ' ';

		}
	}

	for (i = 0; i < WIDTH; ++i) {

		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';

	}

	for (j = 0; j < HEIGHT; ++j) {

		for (i = 0; i < WIDTH; ++i)  putchar(screen[i][j]);
		putchar('\n');

	}
	return 0;
}
double calculate(TFunс prtf, double* x, int n) {
	double funz,rez,max = -1, min = pow(10, 10);

	for (int i = 0; i < n; i++) {
		funz = prtf(x[i]);
		if (funz > max)
			max = funz;
		if (funz < min)
			min = funz;
	}
	rez = max + min;
	return rez;
}
```
# 3. Результаты работы программы

# 4. Информация о разработчике
Авраменко Дмитрий бИПТ-251
