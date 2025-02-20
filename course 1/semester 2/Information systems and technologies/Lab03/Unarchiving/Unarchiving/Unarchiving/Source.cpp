#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <bitset>
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

void Decompress(fstream& file_s_f, fstream& file_orig, fstream& file_arch, string& name)
{
	char buffer;
	string all_code, one_code, size_orig;
	Read_file_s_f(file_s_f, name);
	file_s_f.close();
	sort(file.begin(), file.end(), comp);
	getline(file_arch, size_orig);
	file_arch.seekg(0, ios::end);
	int size_arch = file_arch.tellg();
	file_arch.seekg(size_orig.length() + 1, ios::beg);
	char* text = new char[size_arch - size_orig.length() - 1];
	file_arch.read(text, size_arch - size_orig.length() - 1);
	file_arch.close();
	cout << "\n***Данные из " << name << ".arch прочитаны***\n";
	cout << "Подсчет...\n";
	for (int g = 0; g < size_arch - size_orig.length() - 1; ++g)
	{
		bitset<8> code((unsigned char)text[g]);
		all_code += code.to_string();
	}
	for (int i = 0; i < all_code.length(); ++i)
	{
		one_code += all_code[i];
		auto it = find_if(file.begin(), file.end(), [one_code](const File& a) {return a.code == one_code; });
		if (it == file.end())
		{
			continue;
		}
		int coun = it - file.begin();
		file_orig.write(reinterpret_cast<char*>(&file[coun].symbol), sizeof(char));
		one_code = "";
	}
	cout << "\n***Подсчитанные данные вснесены в " << name << "***\n";
	file_orig.close();
}

int main()
{
	system("chcp 1251");
	system("cls");
	string name;
	cout << "Внимание! Оба файла (пример: file1.txt.arch, file.txt.s_f) должны находиться в папке с этой программой)\nВведите название исходного файла -> ";
	getline(cin, name);
	fstream file_orig("!" + name, ios::binary | ios::out);
	fstream file_s_f(name + ".s_f", ios::in);
	fstream file_arch(name + ".arch", ios::binary | ios::in);
	check(file_orig, name); check(file_s_f, name); check(file_arch, name);
	cout << "\n\n***Файлы семейства " << name << " открыты***\n";
	Decompress(file_s_f, file_orig, file_arch, name);
	cout << "\n\tРазархивация завершена!";
	return 0;
}