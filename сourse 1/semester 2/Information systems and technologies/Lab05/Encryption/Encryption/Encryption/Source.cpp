#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;
string letter = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

bool check_key(string& key)
{
	if (key.length() > 20)
	{
		cout << "\n\a\t***Длина ключа до 20 символов***\n";
		return true;
	}
	if (key.length() == 0)
	{
		cout << "\n\a\t***Вы не ввели значение***\n";
		return true;
	}
	for (const char& k : key)
	{
		auto iter = letter.find(k);
		if (iter == string::npos)
		{
			cout << "\n\a\t***Символ \"" << k << "\" не является буквой русского алфавита!***\n";
			return true;
		}
	}
	return false;
}

void do_enc(ifstream& file_orig, string& key, ofstream& file_res)
{
	queue <char> c_key;
	for (const char& c : key)
	{
		c_key.push(c);
	}
	char symb;
	while (file_orig.read(&symb, 1))
	{
		auto iter_let = find(letter.begin(), letter.end(), symb);
		if (iter_let == letter.end())
		{
			file_res << symb;
			continue;
		}
		auto iter_c_key = find(letter.begin(), letter.end(), c_key.front());
		c_key.push(c_key.front());
		c_key.pop();
		int res = iter_let - letter.begin() + 1 + (iter_c_key - letter.begin()) + 1;
		if (res <= letter.length())
		{
			file_res << letter[res - 1];
		}
		else
		{
			file_res << letter[res - letter.length() - 1];
		}
	}
}

int main()
{
	system("chcp 1251");
	system("cls");
	string key, name;
	cout << "Введите название файла -> ";
	getline(cin, name);
	ifstream file_orig(name);
	ofstream file_res("(с)" + name);
	if (!file_orig.is_open() || !file_res.is_open())
	{
		perror("");
		return 0;
	}
	do
	{
		cout << "\nВведите ключ (до 20 символов): ";
		getline(cin, key);
	} while (check_key(key));
	do_enc(file_orig, key, file_res);
	return 0;
}
