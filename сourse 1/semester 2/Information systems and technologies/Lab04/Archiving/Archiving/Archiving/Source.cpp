#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <list>
using namespace std;
struct Node
{
	int symbol = 0;
	unsigned int freq = 0;
	Node* left = NULL, * rigth = NULL;
};
list <Node*> lst;
vector <Node> symb_orig(256);

struct Code
{
	string code;
	int symbol;
};
vector <Code> code;

bool comp(Node* a, Node* b)
{
	return a->freq < b->freq;
}

void freq_and_lst(ifstream& file_orig)
{
	char byte;
	while (file_orig.read(&byte, 1))
	{
		symb_orig[(unsigned char)byte].symbol = (unsigned char)byte;
		++symb_orig[(unsigned char)byte].freq;
	}
	for (int i = 0; i < symb_orig.size(); ++i)
	{
		if (symb_orig[i].freq == 0)
		{
			symb_orig.erase(symb_orig.begin() + i);
			--i;
		}
	}
	for (int i = 0; i < symb_orig.size(); ++i)
	{
		Node* p = new Node;
		p->symbol = symb_orig[i].symbol;
		p->freq = symb_orig[i].freq;
		lst.push_back(p);
	}
}

Node* build_Haffman()
{
	while (lst.size() != 1)
	{
		lst.sort(comp);
		Node* Left_child = lst.front();
		lst.pop_front();
		Node* Rigth_child = lst.front();
		lst.pop_front();
		Node* parent = new Node;
		parent->freq = Rigth_child->freq + Left_child->freq;
		parent->left = Left_child;
		parent->rigth = Rigth_child;
		parent->symbol = '-1';
		lst.push_back(parent);
	}
	Node* root = lst.front();
	return root;
}


void code_Haffman(Node* node, string str)
{
	if (!node)
	{
		return;
	}
	if (node->symbol != '-1')
	{
		Code buff;
		buff.code = str;
		buff.symbol = node->symbol;
		code.push_back(buff);
	}
	code_Haffman(node->left, str + "0");
	code_Haffman(node->rigth, str + "1");
}


void out_file_Haff(string& name, int size)
{
	ofstream file_haff(name + ".haf");
	file_haff << size << endl;
	for (int i = 0; i < code.size(); ++i)
	{
		file_haff << code[i].symbol << "\t" << code[i].code << endl;
	}
	file_haff.close();
}

void Compress(string& name, ifstream& file_orig)
{
	string all_code, one_code;
	ofstream file_arch("#" + name, ios::binary);
	if (!file_arch.is_open())
	{
		perror("Error! ");
		exit(-1);
	}
	file_orig.clear();
	int size = file_orig.tellg();
	file_orig.seekg(0, ios::beg);
	char* text = new char[size];
	file_orig.read(text, size);
	out_file_Haff(name, size);
	for (int g = 0; g < size; ++g)
	{
		unsigned char symbol = (unsigned char)text[g];
		all_code += code[find_if(code.begin(), code.end(), [symbol](const Code& a) { return a.symbol == symbol; }) - code.begin()].code;
	}
	for (int i = 0; i < all_code.length(); )
	{
		for (int g = 0; g < 8 && i < all_code.length(); ++g, ++i)
		{
			one_code += all_code[i];
		}
		while (one_code.length() < 8)
		{
			one_code += "0";
		}
		char buff = (char)stoi(one_code, nullptr, 2);
		for (int g = 0; g < 3; ++g)
		{
			file_arch << buff;
		}
		one_code = "";
	}
	file_arch.close();
}

int main()
{
	system("chcp 1251");
	system("cls");
	string name, code_str;
	cout << "Введите название исходного файла -> ";
	getline(cin, name);
	ifstream file_orig(name, ios::binary);
	if (!file_orig.is_open())
	{
		perror("Error! ");
		exit(-1);
	}
	freq_and_lst(file_orig);
	Node* root = build_Haffman();
	code_Haffman(root, code_str);
	Compress(name, file_orig);
	file_orig.close();
	return 0;
}