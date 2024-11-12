#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Fio
{
	string surname, name, middlename;
};

struct Employee
{
	Fio fio;
	string post, birthyear, salary;
};

struct
{
	bool flag;
} trfa;

union
{
	int correct = 0;
} corr;

int main()
{
	system("chcp 1251");
	system("cls");
	int choice = 0, amount = 0, numst = 0, yn = 0;
	string temporary;
	vector <Employee> list;
	cout << "\tСтруктура \"Сотрудник\"";
	do
	{
		cout << "\n1 - Внесение нового сотрудника\n2 - Вывод имеющихся сотрудников\n3 - Отсортировать сотрудников по фамилии в алфавином порядке\n4 - Поиск сотрудников по фамилии\n5 - Изменение данных имеющихся сотрудников\n6 - Удаление данных сотрудника\nЛюбое другое число - Выход\nВыберите вариент действия: ";
		cin >> choice;
		cout << "\v";
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
			cout << "Должность: ";
			cin >> list[amount].post;
			cout << "Год рождения: ";
			cin >> list[amount].birthyear;
			cout << "Зароботная плата: ";
			cin >> list[amount].salary;
			amount++;
			cout << "\n***Данные внесены***\n";
			break;
		}
		case 2:
		{
			if (amount == 0)
			{
				system("cls");
				cout << "***Список пуст***\n";
				break;
			}
			else
			{
				system("cls");
				for (int i = 0; i < amount; i++)
					cout << i + 1 << ") " << list[i].fio.surname << " " << list[i].fio.name << " " << list[i].fio.middlename << ", " << list[i].post << ", " << list[i].birthyear << " года, " << list[i].salary << " руб." << endl;
			}
			break;
		}
		case 3:
		{
			if (amount == 0)
			{
				system("cls");
				cout << "***Список пуст***\n";
				break;
			}
			else
			{
				do
				{
					trfa.flag = false;
					for (int bysurname1 = 0; bysurname1 < amount; bysurname1++)
					{
						for (int bysurname2 = 0; bysurname2 < amount; bysurname2++)
						{
							for (int i = 0; i < list[bysurname1].fio.surname.length() && i < list[bysurname2].fio.surname.length(); i++)
							{
								if (list[bysurname1].fio.surname[i] == list[bysurname2].fio.surname[i])
									continue;
								else if (list[bysurname1].fio.surname[i] > list[bysurname2].fio.surname[i])
								{
									swap(list[bysurname1], list[bysurname2]);
									bysurname1 = bysurname2;
									trfa.flag = true;
									break;
								}
								else
								{
									bysurname1 = bysurname2;
									break;
								}
							}
						}
					}
				} while (trfa.flag == true);
			}
			cout << "***Сортировка выполнена успешно***\n";
			break;
		}
		case 4:
		{
			if (amount == 0)
			{
				system("cls");
				cout << "***Список пуст***\n";
				break;
			}
			else
			{
				cout << "Введите фамилию сотрудника: ";
				cin >> temporary;
				cout << "Результат поиска:\n";
				trfa.flag = false;
				for (int i = 0; i < amount; i++)
				{
					if (list[i].fio.surname == temporary)
					{
						trfa.flag = true;
						cout << i + 1 << ")" << list[i].fio.surname << " " << list[i].fio.name << " " << list[i].fio.middlename << ", " << list[i].post << ", " << list[i].birthyear << " года, " << list[i].salary << " руб." << endl;
					}
				}
				if (trfa.flag == false)
					cout << "\n***Нет результатов***\n";
			}
			break;
		}
		case 5:
		{
			if (amount == 0)
			{
				system("cls");
				cout << "***Список пуст***\n";
				break;
			}
			else
			{
				cout << "Введите номер сотрудника, данные которого необходимо изменить: ";
				cin >> corr.correct;
				system("cls");
				do
				{
					cout << "1) Фамилия: " << list[corr.correct - 1].fio.surname << "\n2) Имя: " << list[corr.correct - 1].fio.name << "\n3) Отчество: " << list[corr.correct - 1].fio.middlename << "\n4) Должность: " << list[corr.correct - 1].post << "\n5) Год рождения: " << list[corr.correct - 1].birthyear << "\n6) Зарплата (руб.): " << list[corr.correct - 1].salary << endl;
					cout << "Введите номер строки, которую хотите изменить: ";
					cin >> numst;
					switch (numst)
					{
					case 1:
					{
						cout << "Изменённая фамилия: ";
						cin >> list[corr.correct - 1].fio.surname;
						break;
					}
					case 2:
					{
						cout << "Изменённое имя: ";
						cin >> list[corr.correct - 1].fio.name;
						break;
					}
					case 3:
					{
						cout << "Изменённое отчество: ";
						cin >> list[corr.correct - 1].fio.middlename;
						break;
					}
					case 4:
					{
						cout << "Изменённая должность: ";
						cin >> list[corr.correct - 1].post;
						break;
					}
					case 5:
					{
						cout << "Изменённый год рождения: ";
						cin >> list[corr.correct - 1].birthyear;
						break;
					}
					case 6:
					{
						cout << "Изменённая зарплата: ";
						cin >> list[corr.correct - 1].salary;
					}
					default:
						break;
					}
					cout << "Желаете изменить ещё информацию про этого сотрудника? (1 - да, любое другое число - нет): ";
					cin >> yn;
				} while (yn == 1);
			}
			system("cls");
			break;
		}
		case 6:
		{
			if (amount == 0)
			{
				system("cls");
				cout << "***Список пуст***\n";
				break;
			}
			else
			{
				cout << "Введите номер сотрудника, которого необходимо удалить: ";
				cin >> corr.correct;
				auto itr = list.cbegin();
				list.erase(itr + (corr.correct - 1));
				cout << "\n***Удаление выполнено успешно!***\n";
				amount--;
			}
			break;
		}
		default:
			break;
		}
	} while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6);
	return(0);
}