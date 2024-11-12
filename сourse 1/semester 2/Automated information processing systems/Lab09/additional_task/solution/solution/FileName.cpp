#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

struct Date
{
	int month, year;
};
struct Fio
{
	string surname, name, middlename;
};
struct Birthday
{
	Fio fio;
	Date date;
};

int main()
{
	system("chcp 1251");
	system("cls");
	vector <Birthday> list;
	int amount = 0, choice = 0;
	bool chek = false;
	cout << "\tСтруктура \"День рождения\"\n";
	do
	{
		cout << "1 - Ввести данные о человеке\n2 - Вывести данные о всех людях\n3 - Показать именинников\nЛюбое другое число - Выход из программы\nВыбранное действие: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
		{
			list.resize(amount + 1);
			cout << "Фамилия: ";
			cin >> list[amount].fio.surname;
			cout << "Имя: ";
			cin >> list[amount].fio.name;
			cout << "Отчество: ";
			cin >> list[amount].fio.middlename;
			cout << "Месяц рождения (цифрами, где январь - 1): ";
			cin >> list[amount].date.month;
			cout << "Год рождения (цифрами): ";
			cin >> list[amount].date.year;
			amount++;
			cout << "\n\t***Данные успешно внесены***\n\n";
			break;
		}
		case 2:
		{
			if (amount == 0)
				cout << "\n***Список пуст!***\n\n";
			else
			{
				for (int i = 0; i < amount; i++)
					cout << i + 1 << ") " << list[i].fio.surname << " " << list[i].fio.name << " " << list[i].fio.middlename << ", " << list[i].date.month << " месяц " << list[i].date.year << " год" << endl;
			}
			break;
		}
		case 3:
		{
			if (amount == 0)
				cout << "***Список пуст!***";
			else
			{
				time_t now = time(0);
				tm* ltm = localtime(&now);
				for (int i = 0; i < amount; i++)
				{
					if (1 + ltm->tm_mon == list[i].date.month)
					{
						cout << "Happy birthday, " << list[i].fio.surname << " " << list[i].fio.name << " " << list[i].fio.middlename << "! Теперь Вам " << ((1970 + ltm->tm_year) - list[i].date.year - 70) << endl;
						chek = true;
					}
					if (chek == false)
						cout << "***Ни у кого нет дня рождения в этом месяце :(***\n";
				}
			}
			break;
		}
		default:
			break;
		}
	} while (choice == 1 || choice == 2 || choice == 3);
	return(0);
}