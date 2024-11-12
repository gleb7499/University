#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int x;
	cout << "Введите номер месяца: ";
	cin >> x;
	if (cin.fail() || (x < 0 && x > 12) || char(cin.peek()) == '.')
	{
		cout << "Введены неверные данные!";
	}
	else
	{
		switch (x)
		{
		case 1: cout << "Зима"; break;
		case 2: cout << "Зима"; break;
		case 3: cout << "Весна"; break;
		case 4: cout << "Весна"; break;
		case 5: cout << "Весна"; break;
		case 6: cout << "Лето"; break;
		case 7: cout << "Лето"; break;
		case 8: cout << "Лето"; break;
		case 9: cout << "Осень"; break;
		case 10: cout << "Осень"; break;
		case 11: cout << "Осень"; break;
		case 12: cout << "Зима"; break;
		}
	}
	return(0);
}
