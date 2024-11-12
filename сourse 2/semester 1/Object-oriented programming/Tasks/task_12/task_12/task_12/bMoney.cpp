#include "bMoney.h"

bMoney::bMoney() : money(0) {}

bMoney bMoney::operator+(const bMoney& sec) const
{
	bMoney res;
	res.money = this->money + sec.money;
	return res;
}

std::istream& operator >>(std::istream& is, bMoney& object)
{
	std::cin.ignore();
	is >> object.money;
	std::cin.ignore();
	return is;
}

std::ostream& operator <<(std::ostream& os, const bMoney& object)
{
	os << "$" + std::to_string(object.money);
	return os;
}