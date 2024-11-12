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

void Read_file_s_f(fstream& file_haff, string& name, int* size_orig)
{
	File buff;
	file_haff >> *size_orig;
	while (file_haff >> buff.symbol >> buff.code)
	{
		file.push_back(buff);
	}
}

void Decompress(fstream& file_haff, fstream& file_orig, fstream& file_arch, string& name)
{
	char buffer;
	string all_code, one_code;
	int size_orig;
	Read_file_s_f(file_haff, name, &size_orig);
	file_haff.close();
	sort(file.begin(), file.end(), comp);
	file_arch.seekg(0, ios::end);
	file_arch.clear();
	int size_arch = file_arch.tellg();
	file_arch.seekg(0, ios::beg);
	char* text = new char[size_arch];
	file_arch.read(text, size_arch);
	file_arch.close();
	string a, b, c;
	bitset<8> code;
	for (int g = 0; g < size_arch; ++g)
	{
		code = (unsigned char)text[g];
		a = code.to_string();
		++g;
		code = (unsigned char)text[g];
		b = code.to_string();
		++g;
		code = (unsigned char)text[g];
		c = code.to_string();
		for (int i = 0; i < 8; ++i)
		{
			if ((a[i] - '0') + (b[i] - '0') + (c[i] - '0') > 1)
			{
				all_code += "1";
			}
			else
			{
				all_code += "0";
			}
		}
	}
	string longest = file[0].code;
	int s_long = longest.length();
	for (int i = 1; i < file.size(); ++i)
	{
		if (file[i].code.length() > longest.length())
		{
			longest = file[i].code;
			s_long = longest.length();
		}
	}
	int count = 0, c_o = 0;
	for (int i = 0; i < all_code.length(); ++i)
	{
		one_code += all_code[i];
		auto it = find_if(file.begin(), file.end(), [one_code](const File& a) {return a.code == one_code; });
		if (it == file.end() && count < s_long)
		{
			++count;
			continue;
		}
		if (count == s_long)
		{
			i -= count + 1;
			cout << "\n***Данные не распознаны***\n";
			count = 0;
			continue;
		}
		count = 0;
		if (++c_o > size_orig)
		{
			break;
		}
		int coun = it - file.begin();
		file_orig.write(reinterpret_cast<char*>(&file[coun].symbol), sizeof(char));
		one_code = "";
	}
	file_orig.close();
}

int main()
{
	system("chcp 1251");
	system("cls");
	string name;
	cout << "Внимание! Оба файла (пример: file1.txt.haf, @#file1.txt) должны находиться в папке с этой программой)\nВведите название исходного файла -> ";
	getline(cin, name);
	fstream file_orig("$@#" + name, ios::binary | ios::out);
	fstream file_haff(name + ".haf", ios::in);
	fstream file_arch("@#" + name, ios::binary | ios::in);
	check(file_orig, name); check(file_haff, name); check(file_arch, name);
	Decompress(file_haff, file_orig, file_arch, name);
	return 0;
}