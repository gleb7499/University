#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Schoolchild
{
	struct
	{
		string surname, name, middlename;
	} Fio;
	struct
	{
		string year, month, day;
	} Date;
	struct
	{
		string index, country, area, district, city, street, house, room;
	} Adress;
	string nationality, school, grade, gender, phonenumber;
	int heigth, weigth;
};

void NewChild(vector <Schoolchild>& list, int* amount)
{
	Schoolchild newchild;
	cout << "Фамилия: ";
	getline(cin, newchild.Fio.surname);
	list.push_back(newchild);
	cout << "Имя: ";
	getline(cin, newchild.Fio.name);
	list.push_back(newchild);
	cout << "Отчество: ";
	getline(cin, newchild.Fio.middlename);
	list.push_back(newchild);
	cout << "Пол (М - мужской, Ж - женский): ";
	cin >> newchild.gender;
	cin.ignore();
	list.push_back(newchild);
	cout << "Национальность: ";
	getline(cin, newchild.nationality);
	list.push_back(newchild);
	cout << "Рост (в сантиметрах): ";
	cin >> newchild.heigth;
	cin.ignore();
	list.push_back(newchild);
	cout << "Вес (в килограммах): ";
	cin >> newchild.weigth;
	cin.ignore();
	list.push_back(newchild);
	cout << "Дата рождения\n\tДень: ";
	cin >> newchild.Date.day;
	cin.ignore();
	list.push_back(newchild);
	cout << "\tМесяц: ";
	cin >> newchild.Date.month;
	cin.ignore();
	list.push_back(newchild);
	cout << "\tГод: ";
	cin >> newchild.Date.year;
	cin.ignore();
	list.push_back(newchild);
	cout << "Номер телефона (без знаков \"+\"/\"-\"/\"()\" и т.п.): +";
	getline(cin, newchild.phonenumber);
	list.push_back(newchild);
	cout << "Домашний адрес:\n\tПочтовый индекс: ";
	getline(cin, newchild.Adress.index);
	list.push_back(newchild);
	cout << "\tСтрана: ";
	getline(cin, newchild.Adress.country);
	list.push_back(newchild);
	cout << "\tОбласть: ";
	getline(cin, newchild.Adress.area);
	list.push_back(newchild);
	cout << "\tРайон: ";
	getline(cin, newchild.Adress.district);
	list.push_back(newchild);
	cout << "\tГород: ";
	getline(cin, newchild.Adress.city);
	list.push_back(newchild);
	cout << "\tУлица: ";
	getline(cin, newchild.Adress.street);
	list.push_back(newchild);
	cout << "\tДом: ";
	getline(cin, newchild.Adress.house);
	list.push_back(newchild);
	cout << "\tКвартира: ";
	getline(cin, newchild.Adress.room);
	list.push_back(newchild);
	cout << "Школа: ";
	getline(cin, newchild.school);
	list.push_back(newchild);
	cout << "Класс: ";
	getline(cin, newchild.grade);
	list.push_back(newchild);
	cout << "\n***Данные внесены***\n";
	amount++;
}

void ShowAllChild(vector <Schoolchild>& list)
{
	int answer;
	cout << "Введите номер человека, информацию про которого хотите увидеть: ";
	cin >> answer;
	cin.ignore();
	cout << "Фамилия: " << list[answer - 1].Fio.surname << endl << "Имя: " << list[answer - 1].Fio.name << endl << "Отчество: " << list[answer - 1].Fio.middlename << endl << "Пол: " << list[answer - 1].gender << endl << "Национальность: " << list[answer - 1].nationality << endl << "Рост: " << list[answer - 1].heigth << " см" << endl << "Вес: " << list[answer - 1].weigth << " кг" << endl << "Дата рождения: " << list[answer - 1].Date.day << ":" << list[answer - 1].Date.month << ":" << list[answer - 1].Date.year << endl << "Номер телефона: +" << list[answer - 1].phonenumber << endl << "Домашний адрес:\n\tПочтовый индекс: " << list[answer - 1].Adress.index << endl << "\tСтрана: " << list[answer - 1].Adress.country << endl << "\tОбласть: " << list[answer - 1].Adress.area << endl << "\tРайон: " << list[answer - 1].Adress.district << endl << "\tГород: " << list[answer - 1].Adress.city << endl << "\tУлица: " << list[answer - 1].Adress.street << endl << "\tДом: " << list[answer - 1].Adress.house << endl << "\tКвартира: " << list[answer - 1].Adress.room << endl << "Школа: " << list[answer - 1].school << endl << "Класс: " << list[answer - 1].grade << endl;
}

void ShowChild(vector <Schoolchild>& list, int* amount)
{
	int answer;
	if (amount == 0)
	{
		system("cls");
		cout << "***Список пуст***\n";
		return;
	}
	system("cls");
	for (int i = 0; i < *amount; i++)
		cout << i + 1 << ") " << list[i].Fio.surname << " " << list[i].Fio.name << " " << list[i].Fio.middlename << endl;
	cout << "\n\nЖелаете увидеть расширенную информацию о человеке? (1 - да, любое другое число - нет): ";
	cin >> answer;
	cin.ignore();
	if (answer == 1)
		ShowAllChild(list);
	else
		return;
}

void SortChild(vector <Schoolchild>& list, int* amount)
{
	bool flag;
	if (amount == 0)
	{
		system("cls");
		cout << "***Список пуст***\n";
		return;
	}
	do
	{
		flag = false;
		for (int bysurname1 = 0; bysurname1 < *amount; bysurname1++)
		{
			for (int bysurname2 = 0; bysurname2 < *amount; bysurname2++)
			{
				for (int i = 0; i < list[bysurname1].Fio.surname.length() && i < list[bysurname2].Fio.surname.length(); i++)
				{
					if (list[bysurname1].Fio.surname[i] == list[bysurname2].Fio.surname[i])
						continue;
					else if (list[bysurname1].Fio.surname[i] > list[bysurname2].Fio.surname[i])
					{
						swap(list[bysurname1], list[bysurname2]);
						bysurname1 = bysurname2;
						flag = true;
					}
					else
					{
						bysurname1 = bysurname2;
					}
				}
			}
		}
	} while (flag == true);
	cout << "***Сортировка выполнена успешно***\n";
}

void FindChild(vector <Schoolchild>& list, int* amount)
{
	string temporary;
	bool flag = true;
	int answer = 0;
	if (amount == 0)
	{
		system("cls");
		cout << "***Список пуст***\n";
		return;
	}
	cout << "Введите фамилию школьника: ";
	getline(cin, temporary);
	cout << "Результат поиска:\n";
	for (int i = 0; i < *amount; i++)
	{
		if (list[i].Fio.surname == temporary)
		{
			flag = false;
			cout << i + 1 << ")" << list[i].Fio.surname << " " << list[i].Fio.name << " " << list[i].Fio.middlename;
			cout << "\n\nЖелаете увидеть расширенную информацию о человеке? (1 - да, любое другое число - нет): ";
			cin >> answer;
			cin.ignore();
			if (answer == 1)
				ShowAllChild(list);
			else
				return;
		}
	}
	if (flag)
		cout << "\n***Нет результатов***\n";
}

void ChangeChild(vector <Schoolchild>& list, int* amount)
{
	int correct = 0, numst = 0, yn = 0, aas = 0;
	if (amount == 0)
	{
		system("cls");
		cout << "***Список пуст***\n";
		return;
	}
	cout << "Введите номер школьника, данные которого необходимо изменить: ";
	cin >> correct;
	cin.ignore();
	system("cls");
	do
	{
		cout << "1) Фамилия: " << list[correct - 1].Fio.surname << endl << "2) Имя: " << list[correct - 1].Fio.name << endl << "3) Отчество: " << list[correct - 1].Fio.middlename << endl << "4) Пол: " << list[correct - 1].gender << endl << "5) Национальность: " << list[correct - 1].nationality << endl << "6) Рост: " << list[correct - 1].heigth << " см" << endl << "7) Вес: " << list[correct - 1].weigth << " кг" << endl << "8) Дата рождения: " << list[correct - 1].Date.day << ":" << list[correct - 1].Date.month << ":" << list[correct - 1].Date.year << endl << "9) Номер телефона: +" << list[correct - 1].phonenumber << endl << "10) Домашний адрес:\n\tПочтовый индекс: " << list[correct - 1].Adress.index << endl << "\tСтрана: " << list[correct - 1].Adress.country << endl << "\tОбласть: " << list[correct - 1].Adress.area << endl << "\tРайон: " << list[correct - 1].Adress.district << endl << "\tГород: " << list[correct - 1].Adress.city << endl << "\tУлица: " << list[correct - 1].Adress.street << endl << "\tДом: " << list[correct - 1].Adress.house << endl << "\tКвартира: " << list[correct - 1].Adress.room << endl << "11) Школа: " << list[correct - 1].school << endl << "12) Класс: " << list[correct - 1].grade << endl;
		cout << "Введите номер строки, которую хотите изменить: ";
		cin >> numst;
		cin.ignore();
		switch (numst)
		{
		case 1:
		{
			cout << "Фамилия: ";
			getline(cin, list[correct - 1].Fio.surname);
			break;
		}
		case 2:
		{
			cout << "Имя: ";
			getline(cin, list[correct - 1].Fio.name);
			break;
		}
		case 3:
		{
			cout << "Отчество: ";
			getline(cin, list[correct - 1].Fio.middlename);
			break;
		}
		case 4:
		{
			cout << "Пол (М - мужской, Ж - женский): ";
			cin >> list[correct - 1].gender;
			cin.ignore();
			break;
		}
		case 5:
		{
			cout << "Национальность: ";
			getline(cin, list[correct - 1].nationality);
			break;
		}
		case 6:
		{
			cout << "Рост (в сантиметрах): ";
			cin >> list[correct - 1].heigth;
			cin.ignore();
			break;
		}
		case 7:
		{
			cout << "Вес (в килограммах): ";
			cin >> list[correct - 1].weigth;
			cin.ignore();
			break;
		}
		case 8:
		{
			cout << "Дата рождения:\n\tДень: ";
			cin >> list[correct - 1].Date.day;
			cin.ignore();
			cout << "\tМесяц: ";
			cin >> list[correct - 1].Date.month;
			cin.ignore();
			cout << "\tГод: ";
			cin >> list[correct - 1].Date.year;
			cin.ignore();
			break;
		}
		case 9:
		{
			cout << "Номер телефона (без знаков \"+\"/\"-\"/\"()\" и т.п.): +";
			getline(cin, list[correct - 1].phonenumber);
			break;
		}
		case 10:
		{
			do
			{
				cout << "Домашний адрес:\n\t1) Почтовый индекс\n\t2) Страна\n\t3) Область\n\t4) Район\n\t5) Город\n\t6) Улица\n\t7) Дом\n\t8) Квартира";
				int ad = 0;
				cout << "\nВведите номер строки, которую хотите изменить: ";
				cin >> ad;
				cin.ignore();
				switch (ad)
				{
				case 1:
				{
					cout << "Почтовый индекс: ";
					getline(cin, list[correct - 1].Adress.index);
					break;
				}
				case 2:
				{
					cout << "\tСтрана: ";
					getline(cin, list[correct - 1].Adress.country);
					break;
				}
				case 3:
				{
					cout << "\tОбласть: ";
					getline(cin, list[correct - 1].Adress.area);
					break;
				}
				case 4:
				{
					cout << "\tРайон: ";
					getline(cin, list[correct - 1].Adress.district);
					break;
				}
				case 5:
				{
					cout << "\tГород: ";
					getline(cin, list[correct - 1].Adress.city);
					break;
				}
				case 6:
				{
					cout << "\tУлица: ";
					getline(cin, list[correct - 1].Adress.street);
					break;
				}
				case 7:
				{
					cout << "\tДом: ";
					getline(cin, list[correct - 1].Adress.house);
					break;
				}
				case 8:
				{
					cout << "\tКвартира: ";
					getline(cin, list[correct - 1].Adress.room);
					break;
				}
				default:
					break;
				}
				cout << "Изменить еще одно поле адреса? (1 - да, любое другое число - нет): ";
				cin >> aas;
				cin.ignore();
			} while (aas == 1);
			break;
		}
		case 11:
		{
			cout << "Школа: ";
			getline(cin, list[correct - 1].school);
			break;
		}
		case 12:
		{
			cout << "Класс: ";
			getline(cin, list[correct - 1].grade);
			break;
		}
		default:
			break;
		}
		cout << "Желаете изменить ещё информацию об этом школьнике? (1 - да, любое другое число - нет): ";
		cin >> yn;
		cin.ignore();
	} while (yn == 1);
	system("cls");
}

void DeleteChild(vector <Schoolchild>& list, int* amount)
{
	int correct = 0;
	if (amount == 0)
	{
		system("cls");
		cout << "***Список пуст***\n";
		return;
	}
	cout << "Введите номер школьника, данные которого необходимо удалить: ";
	cin >> correct;
	cin.ignore();
	list.erase(list.begin() + (correct - 1));
	cout << "\n***Удаление выполнено успешно!***\n";
	amount--;
}

int main(int argc, char* argv[])
{
	string password = "Глеб";
	system("chcp 1251");
	system("cls");
	if (argc < 2)
	{
		cout << "\a***Вы забыли ввести своё имя!***" << endl;
		exit(0);
	}
	if (argv[1] != password)
	{
		cout << "\a***Доступ закрыт***" << endl;
		return 0;
	}
	cout << "Привет, " << argv[1] << endl;
	void (*ask[])(vector <Schoolchild>&, int*) = { NewChild, ShowChild, SortChild, FindChild, ChangeChild, DeleteChild };
	int choice = 0, amount = 0;
	vector <Schoolchild> list;
	cout << "\tСтруктура \"Школьник\"";
	do
	{
		cout << "\n1 - Внесение нового школьника\n2 - Вывод имеющихся школьников\n3 - Отсортировать школьников по фамилии в алфавином порядке\n4 - Поиск школьников по фамилии\n5 - Изменение данных имеющихся школьников\n6 - Удаление данных школьника\nЛюбое другое число - Выход\nВыберите вариент действия: ";
		cin >> choice;
		cin.ignore();
		cout << "\v";
		if (choice < 1 || choice > 6)
			break;
		ask[choice - 1](list, &amount);
	} while (true);
	system("pause");
}