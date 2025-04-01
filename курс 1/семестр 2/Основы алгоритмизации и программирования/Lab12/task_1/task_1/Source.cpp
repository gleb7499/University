#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void check(ifstream& somefile, string& line)
{
	if (somefile.is_open())
		cout << "\n***Файл " << line << " открыт***\n";
	else
	{
		perror("Error! ");
		cout << "***Файл " << line << " не открыт***\n";
		exit(1);
	}
}

void reading(ifstream& file1, ifstream& file2)
{
	string nameres;
	cout << "Введите имя результирующего файла: ";
	getline(cin, nameres);
	ofstream result("..\\..\\..\\Files\\task 1\\" + nameres + ".txt");
	string line1, line2;
	while (getline(file1, line1))
	{
		if (getline(file2, line2))
		{
			line1 += line2;
		}
		result << line1 << endl;
	}
	result.close();
}

int main()
{
	system("chcp 65001");
	system("cls");
	void (*ck[])(ifstream&, string&) = { check };
	string line1, line2;
	line1 = "..\\..\\..\\Files\\task 1\\text1.txt";
	ifstream file1(line1);
	(*ck)(file1, line1);
	line2 = "..\\..\\..\\Files\\task 1\\text2.txt";
	ifstream file2(line2);
	(*ck)(file2, line2);
	reading(file1, file2);
	file1.close();
	file2.close();
	return 0;
}