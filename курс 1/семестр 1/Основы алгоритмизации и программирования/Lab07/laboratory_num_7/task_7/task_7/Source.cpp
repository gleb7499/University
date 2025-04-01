#include <iostream>
using namespace std;
int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUSSIAN");
    const int n = 20;
    const int m = 2;
    int a[n][m];
    int j = 0, k, o;
    cout << "Случайные элементы массива:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] = rand() % 50;
            cout << a[i][j] << " ";
            if (j == 1)
            {
                cout << endl;
            }
        }
    }
    int max = a[0][0] + a[1][0];
    cout << "Использованные элементы массива:\n";
    for (int r = 0; r <= 1; r++)
    {
        if (r == 1)
        {
            cout << a[k][0] << " " << a[k][1] << endl << a[o][0] << " " << a[o][1] << endl;
        }
        else
        {
            for (int i = 1; i < n; i++)
            {
                for (; j < i; j++)
                {
                    j = j;
                    if (a[j][0] + a[j][1] + a[i][0] + a[i][1] > max)
                    {
                        max = a[j][0] + a[j][1] + a[i][0] + a[i][1];
                        k = j;
                        o = i;
                    }
                }
            }
        }
    }
    cout << "Результат: " << max;
    return(0);
}
