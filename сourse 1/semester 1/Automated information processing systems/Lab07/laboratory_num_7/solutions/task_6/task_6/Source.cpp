#include <iostream>
using namespace std;
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	cout << "Введите размер квадратной матрицы: ";
	cin >> n;
	if (char(cin.peek()) == '.' || cin.fail() || n > 16 || n < 2)
	{
		cout << "Введены неверные данные!";
		return(0);
	}
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() % 50;
			cout << "Случайный элемент номер [" << i << "][" << j << "]: " << a[i][j] << endl;
		}
	}
	int num = 0, check = 0, k = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			for (int j1 = 0; j1 < n; j1++) {
				if (a[i][j] == a[i + 1][j1]) {
					break;
				}
				check++;
				if (check == n) {
					num++;
					k++;
					check = 0;
				}
			}
			if (k != 0)
				break;
			k = 0;
		}
		check = 0;
	}
	cout << num;
	return 0;
}
