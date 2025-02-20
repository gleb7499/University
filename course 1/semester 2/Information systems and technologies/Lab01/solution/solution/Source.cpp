#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

void check(ifstream& somefile, string& name)
{
	if (somefile.is_open())
		cout << "\n***Файл " << name << " открыт***\n";
	else
	{
		perror("Error! ");
		exit;
	}
}

int file_size(ifstream& somefile)
{
	somefile.seekg(0, ios::end);
	cout << "\n***Размер в байтах вычислен***\n";
	return somefile.tellg();
}

void freq(vector <int>& counters, ifstream& somefile)
{
	char byte;
	while (somefile.read(&byte, 1))
		counters[(unsigned char)byte]++;
	cout << "\n***Подсчет частоты каждого байта выполнен***\n";
}

double entropy(vector <int>& counters, int filesize)
{
	double ent = 0;
	double p = 0;
	for (int i = 0; i < counters.size(); i++)
	{
		if (counters[i] > 0)
		{
			p = (double)counters[i] / (double)filesize;
			ent -= p * log2(p);
		}
	}
	cout << "\n***Подсчет энтропии выполнен***\n";
	return ent;
}

void output_freq(vector <int>& counters, ofstream& rezult)
{
	for (int i = 0; i < 256; i++)
	{
		if (counters[i] == 0)
			continue;
		else
			rezult << i << "\t" << counters[i] << endl;
	}
}

int kolvo(int filesize, double ent)
{
	int kolvo = (filesize * ent) / 8;
	cout << "\n***Количество информации в файле посчитано***\n";
	return kolvo;
}

void result(string& rez, int filesize, double ent, int quantity, vector <int>& counters)
{
	ofstream rezult(rez);
	rezult << filesize << endl << ent << endl << quantity << endl << endl;
	output_freq(counters, rezult);
	rezult.close();
	cout << "\n\tРЕЗУЛЬТАТЫ ВНЕСЕНЫ\n********************************************************\n";
}

void flesh(ifstream& somefile, vector <int>& counters, string& rez, string& name)
{
	check(somefile, name);
	int filesize = file_size(somefile);
	somefile.seekg(0, ios::beg);
	freq(counters, somefile);
	double ent = entropy(counters, filesize);
	int quantity = kolvo(filesize, ent);
	somefile.close();
	result(rez, filesize, ent, quantity, counters);
}

int main()
{
	system("chcp 1251");
	system("cls");
	vector <int> counters(256);
	string name;
	cout << "Введите название файла -> ";
	getline(cin, name);
	ifstream filerar(name, ios::binary);
	string rez = name + ".tab";
	flesh(filerar, counters, rez, name);
	return 0;
}