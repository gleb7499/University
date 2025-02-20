#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
using namespace std;
int qw = 1;

void check(ifstream& file)
{
	if (file.is_open())
		cout << "\n***Файл №" << qw++ << " открыт***\n";
	else
	{
		perror("Error! ");
		exit(1);
	}
}

void counter(ifstream& file)
{
	string text;
	getline(file, text, '\0');
	file.close();
	sort(text.begin(), text.end());
	text.erase(unique(text.begin(), text.end()), text.end()); //unique возвращает итератор на границу между уникальными элементами, и повторяющимися. erase подчищает за unique все не уникальные
	ofstream result("..\\..\\..\\Files\\task 3\\result.txt");
	for (char& c : text) // цикл for each. Перебирает из коллекции (справа) по одному элементу в переменную (слева)
	{
		result << c << "\t" << bitset<8>(c) << endl; // bitset позволяет выводить двоичное представление числа в виде строки. Создаем объект типа bitset, который содержит 8 битов (или 1 байт). Это означает, что мы можем хранить и обрабатывать значения от 0 до 255 (включительно) в двоичном формате.
	}
	result.close();
}

int main()
{
	system("chcp 65001");
	system("cls");
	void (*ck[])(ifstream&) = { check, counter };
	ifstream file("..\\..\\..\\Files\\task 3\\text23.txt");
	ck[0](file);
	ck[1](file);
	return 0;
}