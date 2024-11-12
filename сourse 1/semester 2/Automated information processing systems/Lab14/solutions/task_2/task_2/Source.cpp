#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Queue
{
	string str;
	Queue* last;
};
Queue* tail = NULL, * head = NULL;

void push(string& str)
{
	Queue* temp = new Queue;
	if (!temp)
	{
		cout << "\a\t***Ошибка выделения динамической памяти\n***";
		exit(-1);
	}
	temp->str = str;
	temp->last = NULL;
	if (head == NULL && tail == NULL)
	{
		head = tail = temp;
		return;
	}
	tail->last = temp;
	tail = temp;
}
string pop()
{
	string str;
	Queue* temp = head;
	str = head->str;
	head = head->last;
	delete temp;
	return str;
}

void check_open(ifstream& somefile)
{
	if (!somefile)
	{
		cout << "\a\t***Не удалось открыть файл***\n";
		perror("");
		exit(-1);
	}
}
int check_num(string& Num)
{
	string numbers = "0123456789";
	if (Num.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return 0;
	}
	else
	{
		for (const char& N : Num)
		{
			for (const char& num : numbers)
			{
				if (N == num)
				{
					break;
				}
				if (num == '9')
				{
					cout << "\a\t***Символ " << N << " должен быть цифрой***" << endl;
					return 0;
				}
			}
		}
	}
	int N = stoi(Num);
	if (N > 33 || N < 2)
	{
		cout << "\a\t***Введенное значение должно быть от 2 до 33***\n";
		return 0;
	}
	return N;
}
int init_N()
{
	string Num;
	int N;
	do
	{
		cout << "Введите число N (от 2 до 33): ";
		getline(cin, Num);
	} while (!(N = check_num(Num)));
	return N;
}
void find_word(int* N, ifstream& file)
{
	string line, out;
	int count = 0;
	bool flag = false;
	getline(file, line, '\0');
	if (!line.empty())
	{
		for (const char& c : line)
		{
			if (c != ' ' && c != '\t' && c != '\n' && c != ',' && c != '-' && c != '.' && c != ':' && c != ';' && c != '!' && c != '?' && c != '(' && c != ')')
			{
				++count;
				out += c;
				flag = true;
			}
			else if (flag)
			{
				if (count == *N)
				{
					push(out);
				}
				out = "";
				flag = false;
				count = 0;
			}
		}
	}
}

void result(ofstream& out)
{
	if (!head)
	{
		cout << "\a\t***Нет результатов***\n";
		exit(0);
	}
	while (head)
	{
		out << pop() << " ";
	}
}

int main()
{
	system("chcp 1251");
	system("cls");
	ifstream file("..\\files\\text.txt");
	check_open(file);
	int N = init_N();
	find_word(&N, file);
	file.close();
	ofstream out("..\\files\\result.txt");
	result(out);
	out.close();
	return 0;
}