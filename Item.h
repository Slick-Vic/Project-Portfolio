#pragma once

#include <iostream>
#include "Character.h"

using namespace std;

class Character;

class Item {
public:
	Item(std::string name, int stat, int price);
	Item(const Item&);

	std::string getName();
	int getStat();
	int getPrice();

	virtual void use(Character&);

	friend ostream& operator<<(ostream&, const Item&);

	friend void swap(Item*&, Item*&);

protected:
	std::string mName;
	int mStat;
	int mPrice;
};