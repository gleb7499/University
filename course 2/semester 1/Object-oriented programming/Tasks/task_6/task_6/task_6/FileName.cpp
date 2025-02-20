#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class fraction
{
	int num, den;
public:
	fraction(const string& str)
	{
		stringstream ss(str);
		char ignore;
		ss >> num >> ignore >> den;
	}
	fraction(const int& num, const int& den)
	{
		this->num = num;
		this->den = den;
	}
	fraction operator + (const fraction& obj)
	{
		int _num = num * obj.den + den * obj.num, _den = den * obj.den, g = gcd(_num, _den);
		return { _num /= g, _den /= g };
	}
	const static void display(const fraction& obj)
	{
		(obj.num % obj.den == 0 ? cout << obj.num / obj.den : cout << obj.num << "/" << obj.den) << endl;
	}
private:
	int gcd(int num, int den)
	{
		if (den == 0)
			return num;
		return gcd(den, num % den);
	}
};

bool check(const string& str)
{
	stringstream ss(str);
	char ignore;
	int num, den;
	ss >> num >> ignore >> den;
	if (den == 0)
	{
		cout << "\a\t***Знаменатель не может быть нулем!***\n";
		return true;
	}
	return false;
}

int main()
{
	system("chcp 1251");
	system("cls");
	string str;
	char x;
	bool flag = false;
	while (true)
	{
		do
		{
			cout << "Введите дробное число 1 -> ";
			getline(cin, str);
		} while (check(str));
		fraction a(str);
		do
		{
			cout << "Введите дробное число 2 -> ";
			getline(cin, str);
		} while (check(str));
		fraction b(str);
		cout << "Результат сложения: "; fraction::display(a + b);
		do
		{
			cout << "Продолжить ввод? (y/n) -> ";
			cin >> x;
			cin.ignore();
			if (x == 'n' || x == 'N')
				return 0;
			else if (x != 'y' && x != 'Y')
				flag = true;
		} while (flag);
	}
}