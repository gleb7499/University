#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;
struct Tree
{
	int num;
	Tree* left, * right;
};
Tree* root = NULL;
struct Queue
{
	int num;
	Queue* last;
};
Queue* head = NULL, * tip = NULL;

void init_q(const int* num)
{
	Queue* lst = new Queue;
	lst->last = NULL;
	lst->num = *num;
	tip = lst;
	head = lst;
}
void put(const int* num, Queue*& prev)
{
	Queue* lst = new Queue;
	lst->last = NULL;
	lst->num = *num;
	prev = lst;
	tip = lst;
}
int take_off()
{
	int num = head->num;
	Queue* lst = head;
	head = head->last;
	delete lst;
	return num;
}

Tree* push(Tree*& node, const int* num)
{
	if (node == NULL)
	{
		node = new Tree;
		node->left = NULL;
		node->right = NULL;
		node->num = *num;
	}
	else if (*num < node->num)
	{
		node->left = push(node->left, num);
	}
	else if (*num > node->num)
	{
		node->right = push(node->right, num);
	}
	return node;
}
Tree* MAX(Tree* node)
{
	if (node->right == NULL)
	{
		put(&node->num, head->last);
		node->num = take_off();
	}
	else
	{
		MAX(node->right);
	}
	return node;
}
Tree* MIN(Tree* node)
{
	if (node->left == NULL)
	{
		init_q(&node->num);
		MAX(root);
		node->num = take_off();
	}
	else
	{
		MIN(node->left);
	}
	return node;
}
void printTree(Tree* node, int space)
{
	if (node == NULL)
	{
		return;
	}
	space += 10;
	printTree(node->right, space);
	cout << endl;
	for (int i = 10; i < space; i++)
	{
		cout << " ";
	}
	cout << node->num << "\n";
	printTree(node->left, space);
}

int check_ans(string& ans)
{
	if (ans.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***\n";
		return 0;
	}
	string num = "0123456789";
	for (const char& a : ans)
	{
		for (const char& n : num)
		{
			if (a == n)
			{
				break;
			}
			if (a != n && n == '9')
			{
				cout << "\a\t***Строка должная состоять только из чисел***\n";
				return 0;
			}
		}
	}
	int an = stoi(ans);
	if (an > 100 || an == 0)
	{
		cout << "\a\t***Неверный ввод***\n";
		return 0;
	}
	return an;
}

int main()
{
	srand(time(0));
	system("chcp 1251");
	system("cls");
	string c_no;
	int no, c;
	do
	{
		cout << "Введите количество узлов дерева (до 100): ";
		getline(cin, c_no);
	} while (!(no = check_ans(c_no)));
	c = 50;
	push(root, &c);
	for (int i = 0; i < no - 1; i++)
	{
		c = rand() % 100;
		push(root, &c);
	}
	cout << "\nРезультат заполнения бинарного дерева случайными числами:\n";
	printTree(root, 10);
	MIN(root);
	cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;
	printTree(root, 10);
	return 0;
}