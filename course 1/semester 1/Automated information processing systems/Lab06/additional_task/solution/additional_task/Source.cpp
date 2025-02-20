#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int x, k = 0, g;
	cout << "Введите целое число (кроме нуля): ";
	cin >> x;
	if (char(cin.peek()) == '.' || cin.fail() || x == 0)
	{
		cout << "Введены неверные данные!";
	}
	else
	{
		if (x % 2 == 0)
		{
			cout << "Чётное\n";
		}
		else
		{
			cout << "Не чётное\n";
		}
		if (x < 0)
		{
			cout << "Отрицательное\n";
		}
		else
		{
			cout << "Положительное\n";
		}
		if (x == 0 || x == 1 || x < 0)
		{
			cout << "Не простое и не составное";
		}
		else
		{
			for (int i = 1; i <= x; i++)
			{
				if (x % i == 0)
				{
					k++;
				}
			}
			if (k > 2)
			{
				cout << "Составное\nВсе делители числа:\n";
				for (int l = 1; l <= x; l++)
				{
					if (x % l == 0)
					{
						cout << l << endl;
					}
				}
			}
			else
			{
				cout << "Простое";
			}
		}
	}
	return(0);
}