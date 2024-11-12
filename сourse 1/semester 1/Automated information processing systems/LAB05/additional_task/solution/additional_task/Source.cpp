#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int x;
    cout << "Введите x: ";
    cin >> x;
    for (int i = 1; 0 <= x; i++) {
        if (x == 1) return 0;

        if (x % 2 == 0) {
            x = x / 2;
        }
        else if (x % 2 != 0) {
            x = 3 * x + 1;
        }
        cout << x << endl;
    }
    return(0);
}