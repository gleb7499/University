#include <iostream>
#include <math.h>
#include <locale.h>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    const int n = 4096;
    char str[n] = "";
    int num = 0, max = 0, len = 0, p = 0;
    cout << "Введите данные (до 4096): ";
    cin.getline(str, n);
    for (int i = 0; str[i] != '\0'; i++)
        len++;
    for (int i = 0; i < len / 2; i++)
    {
        swap(str[i], str[len - i - 1]);
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '1')
        {
            num += pow(2, p);
            p++;
        }
        else if (str[i] == '0')
            p++;
        else if (num > max)
        {
            max = num;
            p = 0;
            num = 0;
        }
        else
            p = 0;
    }
    cout << "Полученное число: " << max;
    return 0;
}
