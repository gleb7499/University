#pragma once

#include <string>
#include <sstream>
#include <iostream>

class bMoney
{
	long double money;
public:
	bMoney();
	bMoney operator +(const bMoney& sec) const;
	friend std::istream& operator >>(std::istream& is, bMoney& object);
	friend std::ostream& operator <<(std::ostream& os, const bMoney& object);
};
