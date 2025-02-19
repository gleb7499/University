#include <iostream>
#include <vector>
using namespace std;

class employee
{
private:
	static unsigned int count;
	int id;
	float salary;
public:
	employee(float salary)
	{
		this->salary = salary;
		this->id = ++count;
	}
	static void display(vector <employee>& list_emp)
	{
		for (const auto& emp : list_emp)
		{
			cout << "Зарплата сотрудника с id " << emp.id << " равна " << emp.salary << endl;
		}
	}
};
unsigned int employee::count = 0;

int main()
{
	setlocale(LC_ALL, "ru");
	float salary = 0;
	vector <employee> list_emp;
	for (int i = 1; i <= 3; ++i)
	{
		cout << "Введите зарплату " << i << "-го сотрудника -> ";
		cin >> salary;
		employee emp = salary;
		list_emp.push_back(emp);
	}
	cout << endl;
	employee::display(list_emp);
	return 0;
}