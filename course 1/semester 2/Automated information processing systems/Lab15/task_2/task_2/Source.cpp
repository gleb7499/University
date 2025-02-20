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
	else if (*num <= node->num)
	{
		node->left = push(node->left, num);
	}
	else if (*num > node->num)
	{
		node->right = push(node->right, num);
	}
	return node;
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
		n = rand() % 20;
		root = push(root, &n);
	}
}
void init_key(int* T)
{
	string answer;
	do
	{
		cout << "\nВведите ключ поиска (до 100): ";
		getline(cin, answer);
	} while (!(*T = check_ans(answer)));
}
void print_Tree(Tree* node, int space)
{
	if (node == NULL)
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
Tree* first_el(Tree* lst, int key)
{
	if (!lst)
	{
		return NULL;
	}
	if (key == lst->num)
	{
		return lst;
	}
	if (key < lst->num)
	{
		first_el(lst->left, key);
	}
	else if (key > lst->num)
	{
		first_el(lst->right, key);
	}
	return NULL;
}
Tree* min_node(Tree* node)
{
	if (!node->left)
	{
		return node;
	}
	min_node(node->left);
	return NULL;
}
Tree* delete_all(Tree* lst, int key)
{
	if (!lst)
	{
		return NULL;
	}
	if (key < lst->num)
	{
		lst->left = delete_all(lst->left, key);
	}
	else if (key > lst->num)
	{
		lst->right = delete_all(lst->right, key);
	}
	else
	{
		while (lst != NULL && lst->num == key)
		{
			if (!lst->left)
			{
				Tree* temp = lst->right;
				delete lst;
				lst = temp;
			}
			else if (!lst->right)
			{
				Tree* temp = lst->left;
				delete lst;
				lst = temp;
			}
			else
			{
				Tree* temp = min_node(lst->right);
				lst->num = temp->num;
				lst->right = delete_all(lst->right, temp->num);
			}
		}
		if (lst != NULL)
		{
			lst->left = delete_all(lst->left, key);
			lst->right = delete_all(lst->right, key);
		}

	}
	return lst;
}

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));
	fill_tree();
	cout << "Результат заполнения дерева случайными числами:\n";
	print_Tree(root, 10);
	int key = 0;
	string buff;
	init_key(&key);
	Tree* prev = first_el(root, key);
	cout << "\n\nРезультат поиска:\n";
	if (!prev)
	{
		cout << "\tНет результатов\n";
	}
	else
	{
		cout << prev->num << endl;
	}
	cout << "\n\nНажмите enter, для поиска и удаления всех найденных элементов...";
	getline(cin, buff);
	delete_all(root, key);
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	print_Tree(root, 10);
	return 0;
}