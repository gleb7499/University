#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
class angle {
protected:
	int degrees;
	float min;
	char direction;
	angle() : degrees(0), min(0), direction(0) {}
	void set_angle(const string& data) {
		stringstream _data(data);
		char ignore;
		_data >> degrees >> ignore >> min >> ignore >> direction;
	}
};

class ship : public angle {
	int imo;
	string owner, oper;
public:
	ship() : imo(0), owner(""), oper("") {}
	void set(const int& imo, const string& owner, const string& oper, const string& data) {
		this->imo = imo;
		this->owner = owner;
		this->oper = oper;
		angle::set_angle(data);
	}
	template<size_t N> static const void display(const ship(&mass)[N]) {
		cout << "\nIMO\t" << "Owner\t" << "Operation\t" << "Angle\n";
		cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;
		for (const auto& m : mass) {
			cout << m.imo << "\t" << m.owner << "\t" << m.oper << "\t" << m.degrees << "°" << m.min << "'" << m.direction << endl;
		}
	}
};

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	const size_t SIZE = 3;
	ship mass[SIZE];
	int imo;
	string owner, oper, ang;
	for (int i = 0; i < 3; ++i) {
		cout << i+1 << " Корабль\n\tIMO: ";
		cin >> imo;
		cin.ignore();
		cout << "\tВладелец: ";
		getline(cin, owner);
		cout << "\tОператор: ";
		getline(cin, oper);
		cout << "\tКоординаты (разделяя данные знаком \"/\"): ";
		getline(cin, ang);
		mass[i].set(imo, owner, oper, ang);
	}
	ship::display(mass);
	return 0;
}