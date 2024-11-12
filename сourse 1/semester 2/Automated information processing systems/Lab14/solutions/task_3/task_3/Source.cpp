#include <iostream>
#include <string>
#include <ctime>
using namespace std;
struct Node
{
	int box;
	Node* next;
};
Node* head;

void check_mem(Node* ptr)
{
	if (!ptr)
	{
		cout << "\t\a***Ошибка выделения динамической памяти***";
		exit(-1);
	}
}
Node* root(int* num)
{
	Node* last = new Node;
	check_mem(last);
	last->box = *num;
	last->next = NULL;
	head = last;
	return(last);
}
Node* fill(int* b, Node* last)
{
	Node* n_last = new Node;
	check_mem(n_last);
	n_last->box = *b;
	n_last->next = NULL;
	last->next = n_last;
	return(n_last);
}

bool check_ans(const string& answer)
{
	if (answer.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***";
		return true;
	}
	if (answer == "$")
	{
		exit(0);
	}
	if (answer != "1" && answer != "2")
	{
		cout << "\t\a***Неверный выбор***";
		return true;
	}
	return false;
}
int check_num(const string& answer)
{
	string numbers = "0123456789";
	if (answer == "0" || answer == "1")
	{
		cout << "\a\t***Размер списка не может быть равным нулю или единице***" << endl;
		return 0;
	}
	if (answer.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return 0;
	}
	for (const char& ans : answer)
	{
		for (const char& num : numbers)
		{
			if (ans == num)
			{
				break;
			}
			if (num == '9')
			{
				cout << "\a\t***Допустимы только цифры***" << endl;
				return 0;
			}
		}
	}
	return stoi(answer);
}

void print()
{
	if (!head)
	{
		cout << "\t***Список пуст***" << endl;
		return;
	}
	Node* lst = head;
	while (lst)
	{
		cout << lst->box << " ";
		lst = lst->next;
	}
	cout << endl << endl;
}
void clean()
{
	Node* lst = head, * prev;
	while (lst)
	{
		prev = lst;
		lst = lst->next;
		delete prev;
	}
	head = NULL;
}
void init_node()
{
	clean();
	int num = rand() % 100, ans = 0;
	string answer;
	do
	{
		cout << "Введите размер списка: ";
		getline(cin, answer);
	} while (!(ans = check_num(answer)));
	Node* nb = root(&num);
	for (int i = 1; i < ans; i++)
	{
		num = rand() % 100;
		nb = fill(&num, nb);
	}
	cout << "Результат заполнения списка случайными числами до подсчета: " << endl;
	print();
	nb = head;
	Node* prev = nb->next;
	ans = nb->box;
	while (prev)
	{
		num = prev->box;
		prev->box = ans + num;
		nb = nb->next;
		prev = prev->next;
		ans = num;
	}
	cout << "Результат заполнения после увеличения: " << endl;
	print();
}

int main()
{
	srand(time(0));
	system("chcp 1251");
	system("cls");
	string answer;
	void (*menu[])() = { init_node, print };
	while (true)
	{
		cout << "Выберите действие\n1 - Создание списка\n2 - Просмотр, созданного после увеличения, списка\n$ - Выход из программы";
		do
		{
			cout << "\nВаш выбор: ";
			getline(cin, answer);
		} while (check_ans(answer));
		system("cls");
		menu[stoi(answer) - 1]();
	}
}