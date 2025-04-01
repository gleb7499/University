#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	long double a, b;
	cout << "Введите число a: ";
	cin >> a;
	if (cin.fail() || a <= 0 || char(cin.peek()) == '.')
	{
		cout << "Введено не число!";
	}
	else
	{
		cout << "Введите число b: ";
		cin >> b;
		if (cin.fail() || char(cin.peek()) == '.')
		{
			cout << "Неверный ввод!";
		}
		else
		{
			if (a < b)
			{
				cout << a / b - 1;
			}
			else if (a == b)
			{
				cout << 25 - a;
			}
			else if (a > b)
			{
				cout << (b - 5) / a;
			}
		}
	}
	return(0);
}
