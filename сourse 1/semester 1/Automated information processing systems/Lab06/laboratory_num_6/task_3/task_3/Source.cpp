#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int n, m, k, x = 0, g = 0, counter = 0;
	cout << "Введите число n: ";
	cin >> n;
	if (n < 1 || char(cin.peek()) == '.' || cin.fail())
	{
		cout << "Введены неверные данные!";
		return(0);
	}
	else
	{
		cout << "Введите число m: ";
		cin >> m;
		if (m < 1)
		{
			cout << "Введены неверные данные!";
			return(0);
		}
		else
		{
			for (; n > 0; n--)
			{
				x = n;
				while (x > 0)
				{
					k = x % 10;
					g += k * k * k;
					x /= 10;
				}
				if (g == m)
				{
					cout << ++counter << ") " << n << "\n";
				}
				g = 0;
				k = 0;
				x = 0;
			}
		}
	}
	return(0);
}
