#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

class tollBooth
{
private:
	static unsigned int count;
	static double pay;
public:
	static void payingCar()
	{
		cout << "\nПроехал и заплатил\n";
		++count;
		pay += 0.5;
	}
	static void nopayCar()
	{
		cout << "\nХалявщик\n";
		++count;
	}
	static void display()
	{
		cout << endl << setw(100) << setfill('-') << "" << setfill(' ');
		cout << "\n\n\tОбщее количество машин -> " << count << "\t\tВыручка от оплаты проезда -> " << pay << " $" << endl;
	}
};
unsigned int tollBooth::count = 0;
double tollBooth::pay = 0.0;

int main()
{
	setlocale(LC_ALL, "ru");
	while (true)
	{
		cout << "\n\t1 - Машина проехала и заплатила\t\t2 - Машина только проехала\tEsc - Выход\n";
		switch (_getch())
		{
		case 49: 
			tollBooth::payingCar();
			break;
		case 50: 
			tollBooth::nopayCar();
			break;
		case 27:
			tollBooth::display();
			return 0;
		default: 
			cout << "\a\n***Неверный выбор!***\n";
			break;
		}
	}
}