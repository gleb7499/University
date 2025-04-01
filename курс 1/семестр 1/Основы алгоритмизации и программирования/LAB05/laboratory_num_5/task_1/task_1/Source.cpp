#include <iostream>
using namespace std;
int main()

{
	setlocale(LC_ALL, "Russian");
	int x1, x2, y1, y2;
	cout << "Введите координату x1 первого поля (от 1 до 8) через пробел: ";
	cin >> x1;
	if (x1 >= 1 && x1 <= 8)
	{
		cout << "Введите координату y1 первого поля (от 1 до 8) через пробел: ";
		cin >> y1;
		if (y1 >= 1 && y1 <= 8)
		{
			cout << "Введите координату x2 второго поля (от 1 до 8) через пробел: ";
			cin >> x2;
			if (x2 >= 1 && x2 <= 8)
			{
				cout << "Введите координату y2 второго поля (от 1 до 8) через пробел: ";
				cin >> y2;
				if (y2 >= 1 && y2 <= 8)
				{
					if (x1 == x2 || y1 == y2 || x1 - y1 == x2 - y2 || x1 + y2 == x2 + y2)
					{
						cout << "True";
					}
					else
					{
						cout << "False";
					}

				}
				else
				{
					cout << "Введено неверное значение";
					return(0);
				}
			}
			else
			{
				cout << "Введено неверное значение";
				return(0);
			}

		}
		else
		{
			cout << "Введено неверное значение";
			return(0);
		}

	}
	else
	{
		cout << "Введено неверное значение";
		return(0);
	}
	return(0);
}
