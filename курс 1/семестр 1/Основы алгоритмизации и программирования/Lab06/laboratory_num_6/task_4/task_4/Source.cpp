#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int n, g = 1, x = 0;
	cout << "Введите значение для вычисления факториала (от 2 до 10): ";
	cin >> n;
	if (n < 2 || n > 10 || char(cin.peek()) == '.' || cin.fail())
	{
		cout << "Введены неверные значения!";
		return(0);
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			g *= i;
			x += g;
		}
		cout << x;
	}
	return(0);
}
