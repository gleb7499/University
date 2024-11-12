#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	cout << "Введите длину последовательности: ";
	cin >> n;
	if (char(cin.peek()) == '.' || cin.fail())
	{
		cout << "Введены неверные данные!";
		return(0);
	}
	int* a = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		a[i] = rand() % 10;
	cout << "\nПоследовательность из случайных чисел: ";
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	int num = 0, length = 1, maxlength = 1;
	for (int i = 1; i < n; i++) {
		int k = 0;
		if (a[i] < a[i - 1]) {
			length++;
			k++;
		}
		else {
			if (length > maxlength) {
				maxlength = length;
				num = i - maxlength;
			}
			length = 0;
		}
		if (a[i] > a[i - 1]) {
			length++;
		}
		else {
			if (k == 0) {
				if (length > maxlength) {
					maxlength = length;
					num = i - maxlength;
				}
				length = 0;
			}
		}
	}
	cout << "\n\nПолученная последовательность: ";
	for (int i = num; i < num + maxlength; i++) {
		cout << a[i] << " ";
	}
	return 0;
}
