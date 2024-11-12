#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

struct Book
{
	string title, publisher, name, surname, year, cost, price, profit;
} book;

int MaxFI(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].surname.length() + list[i].name.length() > max)
		{
			max = list[i].surname.length() + list[i].name.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}
int MaxTitle(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].title.length() > max)
		{
			max = list[i].title.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}
int MaxYear(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].year.length() > max)
		{
			max = list[i].year.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}
int MaxPub(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].publisher.length() > max)
		{
			max = list[i].publisher.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}
int MaxCost(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].cost.length() > max)
		{
			max = list[i].cost.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}
int MaxPrice(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].price.length() > max)
		{
			max = list[i].price.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}
int MaxProfit(vector <Book>& list, string& leg)
{
	int max = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].profit.length() > max)
		{
			max = list[i].profit.length();
		}
	}
	if (max < leg.length())
	{
		return leg.length();
	}
	return max;
}

void SortBookTitle(vector<Book>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int g = i + 1; g < list.size(); g++)
		{
			if (list[i].title > list[g].title)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookSurname(vector<Book>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int g = i + 1; g < list.size(); g++)
		{
			if (list[i].surname > list[g].surname)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookName(vector<Book>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int g = i + 1; g < list.size(); g++)
		{
			if (list[i].name > list[g].name)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookYear(vector<Book>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int g = i + 1; g < list.size(); g++)
		{
			if (list[i].year < list[g].year)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookPublisher(vector <Book>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int g = i + 1; g < list.size(); g++)
		{
			if (list[i].publisher > list[g].publisher)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookCost(vector <Book>& list)
{
	int buf1, buf2;
	for (int i = 0; i < list.size(); i++)
	{
		buf1 = stoi(list[i].cost);
		for (int g = i + 1; g < list.size(); g++)
		{
			buf2 = stoi(list[g].cost);
			if (buf1 < buf2)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookPrice(vector <Book>& list)
{
	int buf1, buf2;
	for (int i = 0; i < list.size(); i++)
	{
		buf1 = stoi(list[i].price);
		for (int g = i + 1; g < list.size(); g++)
		{
			buf2 = stoi(list[g].price);
			if (buf1 < buf2)
			{
				swap(list[i], list[g]);
			}
		}
	}
}
void SortBookProfit(vector <Book>& list)
{
	int buf1, buf2;
	for (int i = 0; i < list.size(); i++)
	{
		buf1 = stoi(list[i].profit);
		for (int g = i + 1; g < list.size(); g++)
		{
			buf2 = stoi(list[g].profit);
			if (buf1 < buf2)
			{
				swap(list[i], list[g]);
			}
		}
	}
}

void CheckOpenFile(fstream& file)
{
	if (!file.is_open())
	{
		perror("\tError! ");
		exit(1);
	}
}
bool CheckNumber(string& buffer)
{
	string num = "0123456789";
	if (buffer.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return true;
	}
	for (const char& c : buffer)
	{
		for (int i = 0; i <= num.length(); i++)
		{
			if (c == num[i])
			{
				break;
			}
			else if (num[i] == '\0')
			{
				cout << "\a\t***Некорректный ввод! Символ \"" << c << "\" должен быть цифрой***" << endl;
				return true;
			}
		}
	}
	return false;
}
bool CheckYear(string& buffer)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	string num = "0123456789", year1 = "0", year2 = "0";
	bool flag = false;
	if (buffer.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return true;
	}
	for (const char& c : buffer)
	{
		if (c == '-')
		{
			flag = true;
			continue;
		}
		for (int i = 0; i <= num.length(); i++)
		{
			if (c == num[i])
			{
				break;
			}
			else if (num[i] == '\0')
			{
				cout << "\a\t***Символ \"" << c << "\" должен быть цифрой***" << endl;
				return true;
			}
		}
	}
	if (flag)
	{
		for (int i = 0; i < buffer.length(); i++)
		{
			if (buffer[i] == '-')
			{
				flag = false;
				continue;
			}
			if (flag)
			{
				year1 += buffer[i];
				continue;
			}
			year2 += buffer[i];
		}
		int y1 = stoi(year1), y2 = stoi(year2);
		if (y1 < 301 || y1 > ltm->tm_year + 1900 || y2 < 301 || y2 > ltm->tm_year + 1900 || y1 >= y2)
		{
			cout << "\a\t***Некорректные данные!***" << endl;
			return true;
		}
	}
	else
	{
		int buff = stoi(buffer);
		if (buff < 301 || buff > ltm->tm_year + 1900)
		{
			cout << "\a\t***Некорректные данные!***" << endl;
			return true;
		}
	}
	return false;
}
bool CheckDel(string& corr, vector <Book>& list)
{
	if (CheckNumber(corr))
	{
		return true;
	}
	if (corr.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return true;
	}
	if (stoi(corr) > list.size() || stoi(corr) < 1)
	{
		cout << "\a\t***Общее количество книг " << list.size() << "***" << endl;
		return true;
	}
	return false;
}
bool CheckString(string& buffer)
{
	string letter = "оОеЕаАиИнНтТсСрРвВлЛкКмМдДпПёЁуУяЯыЫьъгГзЗбБчЧйЙхХжЖшШюЮцЦщЩэЭфФ";
	if (buffer.length() == 0)
	{
		cout << "\a\t***Вы не ввели значение***" << endl;
		return true;
	}
	for (const char& c : buffer)
	{
		for (int i = 0; i <= letter.length(); i++)
		{
			if (c == letter[i])
			{
				break;
			}
			else if (letter[i] == '\0' && c != '-' && c != ' ')
			{
				cout << "\a\t***Символ \"" << c << "\" должен быть буквой русского алфавита***" << endl;
				return true;
			}
		}
	}
	return false;
}

void NewBook(fstream& file, vector <Book>& list)
{
	string answer;
	do
	{
		do
		{
			cout << "\nИмя автора: ";
			getline(cin, book.name);
		} while (CheckString(book.name));
		do
		{
			cout << "Фамилия автора: ";
			getline(cin, book.surname);
		} while (CheckString(book.surname));
		do
		{
			cout << "Название: ";
			getline(cin, book.title);
			if (book.title.length() == 0)
			{
				cout << "\a\t***Вы забыли ввести данные***";
			}
		} while (book.title.length() == 0);
		do
		{
			cout << "Год написания: ";
			getline(cin, book.year);
		} while (CheckYear(book.year));
		do
		{
			cout << "Издательство: ";
			getline(cin, book.publisher);
			if (book.publisher.length() == 0)
			{
				cout << "\a\t***Вы забыли ввести данные***";
			}
		} while (book.publisher.length() == 0);
		do
		{
			cout << "Себестоимость: ";
			getline(cin, book.cost);
		} while (CheckNumber(book.cost));
		do
		{
			cout << "Цена: ";
			getline(cin, book.price);
		} while (CheckNumber(book.price));
		book.profit = to_string(stoi(book.price) - stoi(book.cost));
		list.push_back(book);
		file << book.title << "#" << book.surname << "#" << book.name << "#" << book.year << "#" << book.publisher << "#" << book.cost << "#" << book.price << "#" << book.profit << endl;
		file.close();
		file.open("..\\..\\data\\file.txt", ios::out | ios::in | ios::app);
		do
		{
			cout << "\n\tВвести еще одну книгу? (1 - да, любой другой символ - нет): ";
			getline(cin, answer);
			if (answer.length() > 1)
				cout << "\a\t***Введите один символ!***" << endl;
			if (answer.length() == 0)
				cout << "\a\t***Вы не ввели значение***" << endl;
		} while (answer.length() > 1 || answer.length() == 0);
	} while (answer == "1");
	if (list.size() == 1)
		return;
	SortBookSurname(list);
	file.close();
	if (remove("..\\..\\data\\file.txt") != 0)
	{
		perror("\t\a***Сортировка выполнена без занесения в файл! ");
		return;
	}
	file.open("..\\..\\data\\file.txt", ios::out | ios::in | ios::app);
	CheckOpenFile(file);
	for (int i = 0; i < list.size(); i++)
	{
		file << list[i].title << "#" << list[i].surname << "#" << list[i].name << "#" << list[i].year << "#" << list[i].publisher << "#" << list[i].cost << "#" << list[i].price << "#" << list[i].profit << endl;
	}
}

void OutBook(fstream& file, vector <Book>& list)
{
	system("cls");
	if (list.size() == 0)
	{
		cout << "\tСписок пуст";
		return;
	}
	int sum;
	int arr[7] = { 0 };
	string leg[] = { "ИФ", "Название", "Год написания", "Издательство", "Себестоимость", "Цена", "Прибыль" };
	int (*max[])(vector <Book>&, string&) = { MaxFI, MaxTitle, MaxYear, MaxPub, MaxCost, MaxPrice, MaxProfit };
	cout.setf(ios::left);
	cout << setw(5) << "No.";
	for (int i = 0; i < 7; i++)
	{
		sum = max[i](list, leg[i]);
		cout << setw(sum += 5) << leg[i];
		arr[i] = sum;
	}
	sum = 0;
	for (int i = 0; i < 7; i++)
	{
		sum += arr[i];
	}
	int bufsum = sum;
	cout << endl << setfill('_') << setw(sum) << "" << setfill(' ') << endl;
	for (int i = 0; i < list.size(); i++)
	{
		sum = 0;
		cout << setw(5) << i + 1;
		cout << setw(arr[sum++]) << list[i].name + " " + list[i].surname;
		cout << setw(arr[sum++]) << list[i].title;
		cout << setw(arr[sum++]) << list[i].year;
		cout << setw(arr[sum++]) << list[i].publisher;
		cout << setw(arr[sum++]) << list[i].cost;
		cout << setw(arr[sum++]) << list[i].price;
		cout << setw(arr[sum++]) << list[i].profit << endl;
	}
	cout << setfill('_') << setw(bufsum) << "" << setfill(' ') << endl << endl;
	cout.unsetf(ios::left);
}

void SortAndPrintBook(fstream& file, vector <Book>& list)
{
	if (list.size() == 0)
	{
		cout << "\tСписок пуст";
		return;
	}
	if (list.size() == 1)
	{
		OutBook(file, list);
		return;
	}
	string answer;
	cout << "\nПо какому признаку отсортировать? По\n1 - Имени автора\n2 - Фамилии автора\n3 - Названию\n4 - Году написания\n5 - Наименованию издательства\n6 - Себестоимости\n7 - Цене\n8 - Прибыли";
	do
	{
		cout << "\nВаш выбор: ";
		getline(cin, answer);
		if (answer != "1" && answer != "2" && answer != "3" && answer != "4" && answer != "5" && answer != "6" && answer != "7" && answer != "8")
			cout << "\a\t***Неверные данные***";
	} while (answer.length() != 1 || (answer != "1" && answer != "2" && answer != "3" && answer != "4" && answer != "5" && answer != "6" && answer != "7" && answer != "8"));
	void (*Sort[])(vector <Book>&) = { SortBookName, SortBookSurname, SortBookTitle, SortBookYear, SortBookPublisher, SortBookCost, SortBookPrice, SortBookProfit };
	Sort[stoi(answer) - 1](list);
	file.close();
	if (remove("..\\..\\data\\file.txt") != 0)
	{
		perror("\t\a***Сортировка выполнена без занесения в файл!***");
		return;
	}
	file.open("..\\..\\data\\file.txt", ios::out | ios::in | ios::app);
	CheckOpenFile(file);
	system("cls");
	for (int i = 0; i < list.size(); i++)
	{
		file << list[i].title << "#" << list[i].surname << "#" << list[i].name << "#" << list[i].year << "#" << list[i].publisher << "#" << list[i].cost << "#" << list[i].price << "#" << list[i].profit << endl;
	}
	OutBook(file, list);
}

void DeleteBook(fstream& file, vector <Book>& list)
{
	string corr;
	if (list.size() == 0)
	{
		cout << "\tСписок пуст";
		return;
	}
	do
	{
		cout << "\nВведите номер книги, которую хотите удалить (введите 0, если хотите вернуться в меню): ";
		getline(cin, corr);
		if (corr == "0")
		{
			return;
		}
	} while (CheckDel(corr, list));
	list.erase(list.begin() + stoi(corr) - 1);
	file.close();
	system("cls");
	if (remove("..\\..\\data\\file.txt") != 0)
	{
		perror("\t\a***Удаление выполнено без занесения в файл! ");
		return;
	}
	file.open("..\\..\\data\\file.txt", ios::out | ios::in | ios::app);
	CheckOpenFile(file);
	for (int i = 0; i < list.size(); i++)
	{
		file << list[i].title << "#" << list[i].surname << "#" << list[i].name << "#" << list[i].year << "#" << list[i].publisher << "#" << list[i].cost << "#" << list[i].price << "#" << list[i].profit << endl;
	}
	cout << "\t***Удаление выполнено успешно***";
}

void Read(fstream& file, vector <Book>& list)
{
	string buffer;
	file.seekg(0, ios::end);
	if (file.tellg() != 0)
	{
		file.seekg(0);
		while (getline(file, book.title, '#'))
		{
			getline(file, book.surname, '#');
			buffer = book.surname;
			CheckString(buffer);
			getline(file, book.name, '#');
			buffer = book.name;
			CheckString(buffer);
			getline(file, book.year, '#');
			buffer = book.year;
			CheckYear(buffer);
			getline(file, book.publisher, '#');
			getline(file, book.cost, '#');
			buffer = book.cost;
			CheckNumber(buffer);
			getline(file, book.price, '#');
			buffer = book.price;
			CheckNumber(buffer);
			getline(file, book.profit);
			buffer = book.profit;
			CheckNumber(buffer);
			list.push_back(book);
		}
	}
}

int main()
{
	system("chcp 1251");
	system("cls");
	vector <Book> list;
	string answer;
	void (*menu[])(fstream&, vector <Book>&) = { NewBook, OutBook, SortAndPrintBook, DeleteBook };
	fstream file("..\\..\\data\\file.txt", ios::out | ios::in | ios::app);
	CheckOpenFile(file);
	Read(file, list);
	cout << "\tСтруктура \"Книга\"";
	do
	{
		cout << "\n1 - Внесение новой книги\n2 - Вывод имеющихся книг\n3 - Сортировка и вывод по признаку\n4 - Удаление\nЛюбой другой символ - выход\n";
		do
		{
			cout << "Ваш выбор: ";
			getline(cin, answer);
			if (answer.length() > 1)
				cout << "\a\t***Вы должны ввести один символ***" << endl;
			else if (answer.length() == 0)
				cout << "\a\t***Вы забыли ввести данные***" << endl;
		} while (answer.length() != 1);
		if (answer != "1" && answer != "2" && answer != "3" && answer != "4")
			break;
		menu[stoi(answer) - 1](file, list);
	} while (true);
	return 0;
}