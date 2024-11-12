#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int l = 1, r, msum = 0, sum = 0, num = 0;
	cout << "Введите максимальный предел: ";
	cin >> r;
	if (char(cin.peek()) == '.' || cin.fail())
	{
		cout << "Введены неверные данные!";
	}
	else if (r >= 1)
	{
		for (; l < r; l++)
		{
			for (int i = 1; i < l; i++)
			{
				if (l % i == 0)
				{
					sum += i;
				}
				if (sum > msum)
				{
					msum = sum;
					num = l;
				}
			}
			sum = 0;
		}
		cout << num;
	}
	return(0);
}
