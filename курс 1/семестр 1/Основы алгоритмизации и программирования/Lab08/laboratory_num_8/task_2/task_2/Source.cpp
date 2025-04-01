#include <iostream>
#include <string>
using namespace std;
int main()
{
    system("chcp 1251");
    system("cls");
    string str;
    int letter = 0, length = 1, output = 0;
    cout << "Введите данные: ";
    getline(cin, str);
    str += ' ';
    cout << "Символы, которые образуют лексико-графическую последовательность:\n";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ' || str[i] != ',' || str[i] != ':' || str[i] != '-')
        {
            if (str[i + 1] != ' ')
            {
                if (str[i] <= str[i + 1])
                    length++;
                else if (str[i] == ' ' || str[i] > str[i + 1])
                    length = 1;
            }
            else if (str[i + 1] == ' ')
            {
                if (length != 1)
                {
                    if (length > output)
                        output = length;
                    length = 1;
                    for (int j = 0; j <= output; j++)
                        cout << str[i - output + j];
                    cout << endl;
                }
            }
        }
    }
    cout << "Длина слова, которое образует самую длинную лексико-графически упорядоченную последовательность: " << output;
    return 0;
}
