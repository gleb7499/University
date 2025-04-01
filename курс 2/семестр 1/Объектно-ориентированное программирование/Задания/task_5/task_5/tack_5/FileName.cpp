#include <iostream>
#include <sstream>
using namespace std;

class angle
{
private:
	int degrees;
	float min;
	char direction;
public:
	angle()
	{
		direction = min = degrees = 0;
	}
	void input(string data)
	{
		stringstream _data(data);
		char ignore;
		_data >> degrees >> ignore >> min >> ignore >> direction;
	}
	const void display()
	{
		cout << degrees << "°" << min << "'" << direction << endl;
	}
};

int main()
{
	system("chcp 1251");
	system("cls");
	angle a;
	string str;
	do
	{
		cout << "Введите координаты, разделяя данные символом \"/\" ($ - выход) -> ";
		getline(cin, str);
		if (str == "$")
		{
			return 0;
		}
		a.input(str);
		a.display();
	} while (true);
}