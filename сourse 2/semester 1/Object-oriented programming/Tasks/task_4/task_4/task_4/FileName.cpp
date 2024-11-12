#include <iostream>
#include <sstream>
using namespace std;

class _date
{
private:
	int month, day, year;
public:
	_date()
	{
		month = day = year = 0;
	}
	void getdate(string date)
	{
		stringstream ss(date);
		char ignore;
		ss >> month >> ignore >> day >> ignore >> year;
	}
	void showdate()
	{
		(month >= 10 ? cout << month : cout << 0 << month) << "/";
		(day >= 10 ? cout << day : cout << 0 << day) << "/";
		(year >= 10 ? cout << year : cout << 0 << year) << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	string date;
	cout << "Введите дату в формате мм/дд/гг -> ";
	getline(cin, date);
	_date d;
	d.getdate(date);
	d.showdate();
	return 0;
}