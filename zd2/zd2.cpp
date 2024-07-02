#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

typedef struct Time_
{
	int h;
	int m;
} Time;

typedef struct Biatlonisti
{
	char fam[30];
	char country[3];
	int count;
	Time time;
}Sportsmans;

Sportsmans Vvod()
{
	Sportsmans a;
	a.time.m = -1;
	a.time.h = -1;
	printf("\nВведите фамилию биатлониста: ");
	scanf("%s", &a.fam);
	printf("\nВведите первые три буквы страны биатлониста: ");
	scanf("%s", &a.country);
	printf("\nВведите количество промахов на двух огневых рубежах: ");
	scanf("%d", &a.count);
	while ((a.time.h < 0 || a.time.h>24) || (a.time.m < 0 || a.time.m>60))
	{
		printf("\nВведите время спортсмена (в формате XX XX): ");
		scanf("%d %d", &a.time.h, &a.time.m);
		if (a.time.h < 0 || a.time.h>23 || a.time.m < 0 || a.time.m>60)
			printf("\n Повторите ввод времени\n");
	}
	return a;
}

void printtable(Sportsmans a)
{
	if (((a.time.h / 10) < 1) && ((a.time.m / 10) < 1))
		printf("| %30s | %3s |      %2d        |0%1d:0%1d|\n", a.fam, a.country, a.count, a.time.h, a.time.m);
	else
		if ((a.time.h / 10) < 1)
			printf("| %30s | %3s |      %2d        |0%1d:%2d|\n", a.fam, a.country, a.count, a.time.h, a.time.m);
		else
			if ((a.time.m / 10) < 1)
				printf("| %30s | %3s |      %2d        |%2d:0%1d|\n", a.fam, a.country, a.count, a.time.h, a.time.m);
			else
				printf("| %30s | %3s |      %2d        |%2d:%2d|\n", a.fam, a.country, a.count, a.time.h, a.time.m);
	printf("---------------------------------------------------------------\n");
}

int del_value(Sportsmans* x, int count)
{
	char i[30];
	int f = -1;
	printf("Введите фамилию биатлониста:\n");
	scanf("%s", &i);
	for (int j = 0; j < count; j++)
		if (strcmp(x[j].fam, i) == 0)
		{
			f = j;
			break;
		}
	if (f >= 0)
	{
		x[f] = x[count - 1];
		return 1;
	}
	else
	{
		printf("Спортсмена не существует\n");
		return 0;
	}
}

void sort(Sportsmans* a, int count)
{
	Sportsmans t;
	int l = 0;
	int flag;
	do
	{
		flag = 0;
		for (int q = count - 2; q >= l; q--)
			if (a[q].time.h * 60 + a[q].time.m + a[q].count*1 >= a[q + 1].time.h * 60 + a[q + 1].time.m+ a[q+1].count * 1)
			{
				t = a[q];
				a[q] = a[q + 1];
				a[q + 1] = t;
				flag = 1;
			}
		l++;
	} while (flag);
}

int strana(Sportsmans* a, int count)
{
	int i, k, sum, j, first = 1, min, minn;
	int* b;
	b = (int*)malloc(sizeof(int) * count);
	for (i = 0; i < count - 1; i++)
		b[i] = 1;
	for (i = 0; i < count - 1; i++)
		if (b[i])
		{
			k = 1;
			sum = a[i].count;
			for (j = i + 1; j < count; j++)
				if (strchr(a[i].country, a[j].country == 0))
				{
					sum += a[j].count;
					k++;
					b[j] = 0;
				}
			if (first)
			{
				min = sum / k;
				minn = i;
				first = 0;
			}
			else
				if (min > sum / k)
				{
					min = sum / k;
					minn = i;
				}
		}
	return minn;
}

void main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int count, n, m, i, nomer;
	Sportsmans* Sportsman, a, pob1, pob2, pob3;
	count = 1;
	m = 1;
	i = 0;
	Sportsman = (Sportsmans*)malloc(sizeof(Sportsmans) * (count));
	while (m != 0)
	{
		printf("\n1-Добавить запись в таблицу\n2-Вывести таблицу на экран\n3-Удалить запись из таблицы\n4-Поиск страны, спортсмены которой допустили наименьшее кол-во промахов\n5-Поиск спортсменов, занявших первые три места\n6-Очистить экран\n0-Выход\n");
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			m = 0;
			break;
		case 1:
			Sportsman = (Sportsmans*)realloc((void*)Sportsman, sizeof(Sportsmans) * (count += 1));
			for (i; i < count - 1; i++)
			{
				Sportsman[i] = Vvod();
			}
			sort(Sportsman, count - 1);
			break;
		case 2:
			printf("---------------------------------------------------------------\n");
			printf("|           ФАМИЛИЯ              |СТРАНА|КОЛ-ВО ПРОМАХОВ|ВРЕМЯ|\n");
			printf("---------------------------------------------------------------\n");
			for (i = 0; i < count - 1; i++)
				printtable(Sportsman[i]);
			break;
		case 3:
			if (del_value(Sportsman, count - 1))
				Sportsman = (Sportsmans*)realloc((void*)Sportsman, sizeof(Sportsmans) * (count -= 1));
			sort(Sportsman, count);
			break;
		case 4:
			nomer = strana(Sportsman, count - 1);
			printf("Страна, спортсмены которой допустили наименьшее кол-во промахов: %s\n", Sportsman[nomer].country);
			break;
		case 5:
			for (int p = 1; p <= 3; p++)
				printtable(Sportsman[p]);
			break;
		case 6:
			system("cls");
			break;
		default:
			printf("\nПовторите ввод.\n");
		}
	}
}
