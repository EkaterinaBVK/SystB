#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <iomanip>
using namespace std;
int factorial(int n)
{
	if (n == 1 || n == 0)
	{
		return 1;
	}
	else
	{
		return n * factorial(n - 1);
	}
}
int factorial2(int i)
{
	if (i == 1 || i == 0)
	{
		return 1;
	}
	else
	{
		return i * factorial2(i - 1);
	}
}
int factorial3(int f)
{
	if (f == 1||f==0)
	{
		return 1;
	}
	else
	{
		return (f) * factorial3(f - 1);
	}
}
//static int o_c(int n, int m, int g)//нахождение остатка
	static int o_c(int n, int a1, int b) //нахождение остатка
	{
		int ca = 1, cb = 0, maska = 1, shift, copeb = b;
		while (ca > cb)
		{
			b = copeb;
			for (int i = 0; i != n; i++)
			{
				if ((a1 & maska) != 0)
					ca = i;
				if ((b & maska) != 0)
					cb = i;
				maska = maska <<1;
			}
			maska = 1;
			ca++;
			cb++;
			shift = ca - cb;
			if (shift < 0)
				return a1;
			b = b <<shift;
			a1 = a1 ^ b;
		}
		return a1;
	}

int main()
{
	system("chcp 1251");
	system("cls");
	int k, r, d,a=0,b=0;
	printf("Введите k(длина инф.сообщений):");
	scanf_s("%d", &k);
	printf("Введите r(степень порожд.многочлена):");
	scanf_s("%d", &r);
	printf("Введите d(мин.код.расст.):");
	scanf_s("%d", &d);

	printf("Введите p(точность):");
	double p;
	scanf_s("%lf", &p);
	//while (p <=1) 
	//{
		//int k = 3;//инф. сообщение
		//int r = 4;//степень порожд.многочлена
		//int d = 4;//мин.код расст.
		/*double p = 0.1;*/
		double Pe;
		double Pe1 = 0;
		int n = k + r;
		for (int i = d; i <= n; i++)
		{
			int f = n - i;
			Pe = (factorial(n) / (factorial2(i) * factorial3(f)) * pow(p, i)) * pow(1 - p, f);
			Pe1 += Pe;
		}
		printf("Верхняя граница ошибки декодирования=");
		std::cout << std::fixed << std::setprecision(10) << Pe1;
		int arr[100];//создание массива 2^k
		arr[0] = 0b0;
		int N = pow(2, k);
		for (int i = 1; i <= pow(2, k); i++)
		{
			arr[i] = arr[i - 1] + 0b1;
		}
		int g = 0b11101;
		//int g = 0b1011;
		for (int i = 1; i <= pow(2, k); i++)//множество кодовых слов=2^k и кодировка
		{
			int m = arr[i] << r;
			int c = 0;
			c = o_c(n, m, g);
			int a = m + c;
			arr[i] = a;//заносим закодированное слово в массив
		}
		int arrwe[100] = { 0 };//создание массива веса
		int Ai[100] = { 0 };
		for (int i = 1; i <= pow(2, k); i++)//подсчет веса каждого слова
		{
			while (arr[i] != 0)
			{
				if (arr[i] % 2 == 1)
					arrwe[i] += 1;
				arr[i] = arr[i] / 2;
			}
			int o = d;
			if (arrwe[i] >= d)
			{
				while (arrwe[i] != o)
					o++;
				Ai[o] += 1;
			}// занесу в отдельный массив вес
		}
		double Pe2 = 0;
		for (int i = d; i <= n; i++)// формула
		{
			int f = n - i;
			Pe = Ai[i] * pow(p, i) * pow(1 - p, f);
			Pe2 += Pe;
		}
		printf("\nТочное значение вероятности ошибки декодирования=");
		std::cout << std::fixed << std::setprecision(10) << Pe2;
		/*k += 1;*/
		//p += 0.1;
	//}
}
