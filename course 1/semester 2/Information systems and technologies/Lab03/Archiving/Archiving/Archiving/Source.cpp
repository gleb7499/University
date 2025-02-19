#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
struct File
{
	int symbol;
	string code;
};
vector <File> file;

bool comp(const File& a, const File& b)
{
	return a.symbol < b.symbol;
}

void check(fstream& somefile, string& name)
{
	if (!somefile.is_open())
	{
		perror("\a\tError! ");
		exit(1);
	}
}

void Read_file_s_f(fstream& file_s_f, string& name)
{
	string buffer;
	getline(file_s_f, buffer);
	getline(file_s_f, buffer);
	getline(file_s_f, buffer);
	File buff;
	while (file_s_f >> buff.symbol >> buff.code)
	{
		file.push_back(buff);
	}
	cout << "\n***Данные из " << name << ".s_f прочитаны***\n";
}

void Compress(fstream& file_s_f, fstream& file_orig, fstream& file_arch, string& name)
{
	char buffer;
	int symbol;
	string all_code, one_code;
	Read_file_s_f(file_s_f, name);
	file_s_f.close();
	sort(file.begin(), file.end(), comp);
	file_orig.seekg(0, ios::end);
	int size = file_orig.tellg();
	file_orig.seekg(0, ios::beg);
	char* text = new char[size];
	file_orig.read(text, size);
	cout << "\n***Данные из " << name << " прочитаны***\n";
	file_arch << size << endl;
	cout << "Подсчет...\n";
	for (int g = 0; g < size; ++g)
	{
		unsigned char symbol = (unsigned char)text[g];
		all_code += file[find_if(file.begin(), file.end(), [symbol](const File& a) { return a.symbol == symbol; }) - file.begin()].code;
	}
	for (int i = 0; i < all_code.length(); )
	{
		for (int g = 0; g < 8 && i < all_code.length(); ++g, ++i)
		{
			one_code += all_code[i];
		}
		while (one_code.length() < 8)
		{
			one_code += "0";
		}
		file_arch << (char)stoi(one_code, nullptr, 2);
		one_code = "";
	}
	cout << "\n***Подсчитанные данные вснесены в " << name << ".arch***\n";
	file_arch.close();
}

int main()
{
	system("chcp 1251");
	system("cls");
	string name;
	cout << "Внимание! Оба файла (пример: file.txt, file.txt.s_f) должны находиться в папке с этой программой)\nВведите название исходного файла -> ";
	getline(cin, name);
	fstream file_orig(name, ios::binary | ios::in);
	fstream file_s_f(name + ".s_f", ios::in);
	fstream file_arch(name + ".arch", ios::binary | ios::out);
	check(file_orig, name); check(file_s_f, name); check(file_arch, name);
	cout << "\n\n***Файлы семейства " << name << " открыты***\n";
	Compress(file_s_f, file_orig, file_arch, name);
	cout << "\n\tАрхивация завершена!";
	return 0;
}