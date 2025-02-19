#include <iostream>
#include <string>
#include <ctime>
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
	Tree* tree;
	Queue* last;
};
Queue* tip = NULL, * beg = NULL;

Tree* push(Tree* node, int* num)
{
	if (!node)
	{
		node = new Tree;
		if (!node)
		{
			cout << "\a\t***Ошибка выделения памяти***\n";
			exit(-1);
		}
		node->num = *num;
		node->left = NULL;
		node->right = NULL;
		return node;
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

void put(Tree* node)
{
	Queue* lst = new Queue;
	lst->last = NULL;
	lst->tree = node;
	if (!beg)
	{
		beg = tip = lst;
		return;
	}
	tip->last = lst;
	tip = lst;
	return;
}
Tree* pop()
{
	Queue* lst = beg;
	Tree* ptr = beg->tree;
	beg = beg->last;
	delete lst;
	return ptr;
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
void fill_tree()
{
	string answer;
	int T, n;
	do
	{
		cout << "Введите количество узлов дерева (до 100): ";
		getline(cin, answer);
	} while (!(T = check_ans(answer)));
	for (int i = 0; i < T; i++)
	{
		n = rand() % 100;
		root = push(root, &n);
	}
}

void preorder()
{
	Tree* prev = root;
	put(prev);
	while (beg)
	{
		prev = pop();
		cout << prev->num << " ";
		if (prev->left)
		{
			put(prev->left);
		}
		if (prev->right)
		{
			put(prev->right);
		}
	}
}

void print_Tree(Tree* node, int space)
{
	if (!node)
	{
		return;
	}
	space += 10;
	print_Tree(node->right, space);
	cout << endl;
	for (int i = 10; i < space; i++)
	{
		cout << " ";
	}
	cout << node->num << "\n";
	print_Tree(node->left, space);
}

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));
	fill_tree();
	cout << "\nРезультат заполнения дерева случайными числами:\n";
	print_Tree(root, 10);
	cout << endl << setfill('_') << setw(70) << "" << setfill(' ') << endl;
	cout << "\nРезультат чтения в ширину:\n";
	preorder();
	return 0;
}