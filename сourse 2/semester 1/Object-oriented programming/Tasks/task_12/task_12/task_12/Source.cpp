#include "bMoney.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	bMoney m_1, m_2;
	cout << "Введите количество денег для m_1 ($0.0) -> ";
	cin >> m_1;
	cout << "Введите количество денег для m_2 ($0.0) -> ";
	cin >> m_2;
	cout << m_1 + m_2;
	return 0;
}