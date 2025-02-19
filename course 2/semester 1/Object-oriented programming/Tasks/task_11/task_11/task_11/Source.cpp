#include "Matrix.h"

#include <string>
#include <iostream>

using namespace std;

int main() {
	system("chcp 1251");
	system("cls");
	Matrix<int> matrix;
	string row;
	while (true) {
		cout << "Введите строку -> ";
		getline(cin, row);
		cout << endl;
		if (row == "$") {
			break;
		}
		matrix.setRow(row);
	}
	cout << "Детерминант -> " << matrix.determinant();
	return 0;
}