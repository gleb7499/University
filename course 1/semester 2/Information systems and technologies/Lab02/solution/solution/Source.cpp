#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
	double frequency = 0.0;
	double chance = 0.0;
	string code;
	int symbol = 0;
};
vector <Node> list(256);

void check(ifstream& somefile)
{
	if (!somefile.is_open())
	{
		perror("Error! ");
		exit(1);
	}
}

void NewLine(ifstream& somefile)
{
	string buffer;
	getline(somefile, buffer);
}

void ReadingAndCount(ifstream& somefile, vector <Node>& list, string& entropy)
{
	double totalfreq = 0.0;
	NewLine(somefile);
	getline(somefile, entropy);
	NewLine(somefile);
	NewLine(somefile);
	for (int i = 0; i < 256; i++)
	{
		somefile >> list[i].symbol;
		somefile >> list[i].frequency;
		totalfreq += list[i].frequency;
	}
	for (int i = 0; i < 256; i++)
	{
		list[i].chance = list[i].frequency / totalfreq;
	}
}

bool comp_1(const Node& a, const Node& b)
{
	return a.frequency > b.frequency;
}

void ShannonFano(vector <Node>& list, int left, int right)
{
	if (left == right)
	{
		return;
	}
	if (left + 1 == right)
	{
		list[left].code += "1";
		list[right].code += "0";
		return;
	}
	double sum = 0;
	for (int i = left; i <= right; i++)
	{
		sum += list[i].frequency;
	}
	if (sum == 0)
	{
		return;
	}
	sum /= 2;
	double aboutsum = list[left].frequency;
	int mid = left;
	while (aboutsum <= sum && mid < right)
	{
		++mid;
		aboutsum += list[mid].frequency;
	}
	for (int i = left; i <= mid; i++)
	{
		list[i].code += "1";
	}
	for (int i = mid + 1; i <= right; i++)
	{
		list[i].code += "0";
	}
	ShannonFano(list, left, mid);
	ShannonFano(list, mid + 1, right);
}

void Math(double* math, vector <Node>& list)
{
	for (int i = 0; i < 256; i++)
	{
		*math += list[i].code.length() * list[i].chance;
	}
}

void result(string& buf2, string& entropy, double* math, vector <Node>& list)
{
	ofstream somefile(buf2 + ".s_f");
	somefile << entropy << endl << *math << endl << endl;
	for (int i = 0; i < 256; i++)
	{
		if (list[i].frequency == 0)
		{
			continue;
		}
		somefile << list[i].symbol << "\t" << list[i].code << endl;
	}
}

void base(string& name)
{
	double math = 0.0;
	string entropy;
	ifstream somefile(name + ".tab");
	check(somefile);
	ReadingAndCount(somefile, list, entropy);
	sort(list.begin(), list.end(), comp_1);
	int left = 0, right = 255;
	ShannonFano(list, left, right);
	somefile.close();
	Math(&math, list);
	result(name, entropy, &math, list);
}

int main()
{
	system("chcp 1251");
	system("cls");
	string name;
	cout << "Введите имя файла (без .tab) -> ";
	getline(cin, name);
	base(name);
	return 0;
}