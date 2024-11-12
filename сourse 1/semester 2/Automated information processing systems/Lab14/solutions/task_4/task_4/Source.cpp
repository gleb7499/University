#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
struct List
{
	int num;
	List* next;
};
List* head = NULL;
List* put(List* last, int* num)
{
	List* lst = new List;
	if (!lst)
	{
		cout << "\a\t***Не удалось выделить динамическую память***\n";
		exit(-1);
	}
	if (!last)
	{
		lst->next = NULL;
		lst->num = *num;
		head = lst;
		return head;
	}
	lst->next = NULL;
	lst->num = *num;
	last->next = lst;
	return(lst);
}

int check_num(string& q)
{
	string numbers = "0123456789";
	if (q.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return 0;
	}
	else
	{
		for (const char& N : q)
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
	int N = stoi(q);
	if (N < 3)
	{
		cout << "\a\t***Количество чисел не может быть меньше 3-ёх***\n";
		return 0;
	}
	return N;
}

void init_file(fstream& file)
{
	string q;
	int quan;
	do
	{
		cout << "Введите количество чисел в файле (минимум 3 числа): ";
		getline(cin, q);
	} while (!(quan = check_num(q)));
	for (int i = 0; i < quan; i++)
	{
		file << rand() % 41 - 20 << " ";
	}
	file.close();
	file.open("..\\files\\numbers.txt", ios::in | ios::out | ios::app);
}
void get_list(fstream& file)
{
	int num;
	List* lst = head;
	cout << endl << "Исходный список: \n";
	while (file >> num)
	{
		cout << num << " ";
		lst = put(lst, &num);
	}
}

void summ_num(fstream& file)
{
	List* lst1 = head;
	List* lst2 = head->next;
	List* lst3 = lst2->next;
	List* ptr = head;
	while (lst3)
	{
		if (lst1->num + lst3->num == lst2->num)
		{
			ptr = ptr->next;
			ptr->num = lst2->num;
		}
		lst1 = lst1->next;
		lst2 = lst2->next;
		lst3 = lst3->next;
	}
	if (ptr == head)
	{
		cout << "\n\tНет результатов\n";
		exit(0);
	}
	lst1 = head;
	head = head->next;
	delete lst1;
	lst1 = ptr;
	ptr = ptr->next;
	lst1->next = NULL;
	while (ptr)
	{
		lst1 = ptr;
		ptr = ptr->next;
		delete lst1;
	}
	cout << endl << endl;
	ptr = head;
	cout << "\nРезультат работы: \n";
	while (ptr)
	{
		cout << ptr->num << " ";
		ptr = ptr->next;
	}
}

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));
	fstream file("..\\files\\numbers.txt", ios::in | ios::out | ios::trunc);
	if (!file)
	{
		perror("");
		return 0;
	}
	init_file(file);
	get_list(file);
	summ_num(file);
	file.close();
	return 0;
}