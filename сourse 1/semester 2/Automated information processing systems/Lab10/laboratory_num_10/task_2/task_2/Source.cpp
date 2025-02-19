#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int BinToDec(string S)
{
    int dec = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if (S[i] == '1')
        {
            dec += pow(2, S.length() - i - 1);
        }
    }
    return dec;
}

int main()
{
    setlocale(LC_ALL, "ru");
    string S;
    int answer = 0;
    do
    {
        cout << "Введите строку: ";
        getline(cin, S);
        cout << "Результат выполнения: " << BinToDec(S);
        cout << "\nЖелаете перевести ещё одно число?\nВведите \"1\", если необходимо продолжить, и любое другое число, для выхода: ";
        cin >> answer;
        cin.ignore();
        cout << endl << endl;
    } while (answer == 1);
    return(0);
}
