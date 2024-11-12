#include <iostream>
#include <vector>
using namespace std;

int counter = 0;

int Fib1(int T)
{
	counter++;
	if (T <= 1)
		return T;
	return Fib1(T - 1) + Fib1(T - 2);
}


void inputN(vector <int>& N)
{
	for (int i = 0; i < 5; ++i)
	{
		cout << "Введите число №" << i + 1 << " : ";
		cin >> N[i];
	}
}

void traN(vector <int>& N)
{
	int T = 0;
	for (int i = 0; i < 5; i++)
	{
		counter = 0;
		T = N[i];
		cout << "\nFib(" << i + 1 << ") = " << Fib1(T) << endl;
		cout << "\tКоличество рекурсивных вызовов Fib1 для числа №" << i + 1 << ": " << counter;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	vector <int> N(5);
	inputN(N);
	traN(N);
	return 0;
}
