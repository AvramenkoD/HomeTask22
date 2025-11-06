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
2. Объявить переменные:
   - `repeatF` - выбор повторения программы
   - `side` - сторона
   - `symbol` - печатаемый симбол
3. Запросить у пользователя side, symbol
4. В цикле `int i` от 1 до side (вкл)
    	a. Перевод каретки на новую строку;
      	b. В цикле `int j` от 1 до side (вкл)
             Выводим `symbol`
6. Спросить у пользователя хочет ли он повторить, если да то к 3 пункту, иначе 7
7. **Конец**

### Блок-схема
![Блок-схема алгоритма](Lab10.1_schema.jpg)

 [Ссылка на блок-схему](https://viewer.diagrams.net/?tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Lab10.1_schema.drawio&dark=auto#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1JpmhIfzJodOCcWVEdJUO9KuQrloiS01t%26export%3Ddownload)

 ## 2. Реализация программы

```c
#include <locale.h>
#include <stdio.h>

int area_square(int);
int Opred();
int Draw(int, int, int, char);
int compareSquare(int, int);
int main()
{
	int repeatF, choise,sidea,sideb, sidec;
	char symbol;

	setlocale(LC_ALL, "RUS");

	do
	{
		repeatF = 0;
		puts("Выберите тип операции:");
		puts("1) Посчитать площадь");
		puts("2) Вывести определение");
		puts("3) Нарисовать фигуру");
		puts("4) Сравнить площади двух фигур");
		scanf("%d", &choise);

		switch (choise)
		{
			case 1:
				printf("Введите сторону квадрата: ");
				scanf("%d", &sidea);
				printf("Площадь = %d", area_square(sidea));
				break;
			case 2:
				Opred();
				break;
			case 3:
				printf("Введите стороны квадратов и символ через пробел: ");
				scanf("%d %d %d %c", &sidea, &sideb, &sidec, &symbol);
				Draw(sidea,sideb,sidec, symbol);
				break;
			case 4:
				printf("Введите стороны квадратов: ");
				scanf("%d %d", &sidea,&sideb);
				printf("%d",compareSquare(sidea, sideb));
				break;
		}

		printf("\nЖелаете повторить 0 - нет, иначе - да: ");
		scanf("%d", &repeatF);

	} while (repeatF);
	puts("");
	system("pause");
}
int area_square(int side)
{
	int S = side * side;
	return S;
}
int Opred()
{
	puts("Квадрат — правильный четырёхугольник, то есть плоский четырёхугольник, у которого все углы и все стороны равны.\n Каждый угол квадрата — прямой");
}
int Draw(int sidea, int sideb, int sidec, char symbol)
{
	int bigSide = sidea + sideb - sidec;
	for (int i = 0; i < bigSide; i++) {

		for (int j = 0; j < bigSide; j++) {
			if (i < bigSide - sideb && j < sidea)
			{
				printf("%c",symbol);
			}
			else if (i >= sidea && j < bigSide - sideb) 
			{
				printf(" ");
			}
			else if (i >= sidea && j >= bigSide - sideb)
			{
				printf("%c", symbol);
			}
			else if (i >= bigSide - sideb && i < bigSide-(sideb-sidec))
			{
				if (j >= bigSide - sidea && j < bigSide - (sidea - sidec))
				{
					printf(" ");
				}
				else
				{
					printf("%c", symbol);
				}
			}
		}
		printf("\n");
	}
}
int compareSquare(int sidea, int sideb)
{
	int S1 = sidea * sidea;
	int S2 = sideb * sideb;
	return S1 > S2 ? S1 - S2 : S2 - S1;
}

```
# 3. Результаты работы программы

# 4. Информация о разработчике
Авраменко Дмитрий бИПТ-251
