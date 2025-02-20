#include <iostream>
#include <string>
using namespace std;

bool check(string& str)
{
	bool space = true;
	if (str.empty())
	{
		cout << "\a\t***Вы не ввели значение!***" << endl;
		return true;
	}
	for (const char& c : str)
	{
		if (c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != ' ' && c != '\t')
		{
			cout << "\a\t***Элемент \"" << c << "\" скобкой не является!***" << endl;
			return true;
		}
		if (c != ' ' && c != '\t')
		{
			space = false;
		}
	}
	if (space)
	{
		cout << "\a\t***Вы ввели только пробел или табуляцию!***" << endl;
		return true;
	}
	return false;
}

bool checkBrackets(string& str)
{
	string staples_open = "([{", staples_close = ")]}";
	int counters[3] = { 0 };
	for (const char& c : str)
	{
		if (c == ' ' || c == '\t')
		{
			continue;
		}
		for (int g = 0; g < 3; g++)
		{
			if (c == staples_open[g])
			{
				counters[g]++;
				break;
			}
			else if (c == staples_close[g])
			{
				counters[g]--;
				if (counters[g] < 0)
				{
					return false;
				}
				break;
			}
		}
	}
	if (counters[0] == 0 && counters[1] == 0 && counters[2] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	system("chcp 1251");
	system("cls");
	string str;
	do
	{
		cout << "Введите строку: ";
		getline(cin, str);
	} while (check(str));
	if (checkBrackets(str))
	{
		cout << "Строка правдива" << endl;
	}
	else
	{
		cout << "Строка ложна" << endl;
	}
	return 0;
}