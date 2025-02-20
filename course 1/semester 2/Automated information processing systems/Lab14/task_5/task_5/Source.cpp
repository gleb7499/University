#include <iostream>
#include <string>
#include <ctime>
using namespace std;
struct List
{
	int num;
	List* next;
};
List* head = NULL;
List* put(List* last, int num)
{
	List* lst = new List;
	if (!lst)
	{
		cout << "\a\t***Не удалось выделить динамическую память***\n";
		exit(-1);
	}
	if (!head)
	{
		lst->num = num;
		lst->next = NULL;
		head = lst;
		return head;
	}
	lst->num = num;
	lst->next = NULL;
	last->next = lst;
	return(lst);
}
void pop_min()
{
	List* lst_1 = head;
	List* lst_2 = lst_1;
	bool flag = false;
	while (lst_2)
	{
		if (lst_2->num >= 0)
		{
			if (flag)
			{
				lst_1 = lst_1->next;
			}
			lst_1->num = lst_2->num;
			flag = true;
		}
		lst_2 = lst_2->next;
	}
	lst_2 = lst_1->next;
	lst_1->next = NULL;
	List* del;
	while (lst_2)
	{
		del = lst_2;
		lst_2 = lst_2->next;
		delete del;
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
					cout << "\a\t***Символ \"" << N << "\" должен быть цифрой***" << endl;
					return 0;
				}
			}
		}
	}
	int N = stoi(Num);
	if (N < 3)
	{
		cout << "\a\t***Неверный размер списка***\n";
		return 0;
	}
	return N;
}

void init_size(int* size)
{
	string answer;
	do
	{
		cout << "Введите число элементов: ";
		getline(cin, answer);
	} while (!(*size = check_num(answer)));
}
void init_M(int* size)
{
	List* lst = head;
	for (int i = 0; i < *size; i++)
	{
		lst = put(lst, rand() % 201 - 100);
	}
}
void print()
{
	List* lst = head;
	while (lst)
	{
		cout << lst->num << " ";
		lst = lst->next;
	}
}

int main()
{
	srand(time(0));
	system("chcp 1251");
	system("cls");
	int size = 0;
	init_size(&size);
	init_M(&size);
	cout << "\nИсходный список чисел:\n";
	print();
	pop_min();
	cout << "\n\nРезультирующий список чисел:\n";
	print();
}