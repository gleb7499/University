#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int qw = 1;

void check(ifstream& file)
{
    if (file)
        cout << "\n***Файл №" << qw++ << " открыт***\n";
    else
    {
        cerr << "Error opening file: " << strerror(errno) << endl;
    }
}

void Paragraph(ifstream& file)
{
    string line;
    int parag = 0;
    bool flag = false;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            flag = true;
        }
        else if (flag == false)
        {
            continue;
        }
        else
        {
            parag++;
            flag = false;
        }
    }
    cout << "Количество абзацев в тексте: " << parag << endl;
}

int main()
{
    system("chcp 65001");
    system("cls");
    void (*ck[])(ifstream&) = { check, Paragraph };
    ifstream file("..\\..\\..\\Files\\task 2\\text27.txt");
    ck[0](file);
    ck[1](file);
    file.close();
    return 0;
}