#include <iostream>
using namespace std;
class _time
{
private:
	int hour, min, sec;
public:
	_time()
	{
		hour = min = sec = 0;
	}
	_time(int hour, int min, int sec)
	{
		this->hour = hour;
		this->min = min;
		this->sec = sec;
	}
	_time operator + (const _time& object)
	{
		int _hour = 0, _min = 0, _sec = 0;
		if (object.sec + this->sec >= 60)
		{
			_sec = object.sec + this->sec - 60;
			++_min;
		}
		else
		{
			_sec = object.sec + this->sec;
		}
		if (object.min + this->min >= 60)
		{
			_min += object.min + this->min - 60;
			++_hour;
		}
		else
		{
			_min += object.min + this->min;
		}
		if (object.hour + this->hour > 12)
		{
			_hour += object.hour + this->hour - 12;
		}
		else
		{
			_hour += object.hour + this->hour;
		}
		return { _hour == 13 ? 1 : _hour, _min, _sec };
	}
	const void display()
	{
		(hour < 10 ? cout << 0 << hour : cout << hour) << ":";
		(min < 10 ? cout << 0 << min : cout << min) << ":";
		(sec < 10 ? cout << 0 << sec : cout << sec) << endl;
	}
};

int main()
{
	_time a = { 12, 5, 59 }, b = { 10, 59, 59 }, c;
	c = a + b;
	c.display();
	return 0;
}