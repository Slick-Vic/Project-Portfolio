#include "Item.h"

//Constructor
Item::Item(std::string name, int stat, int price)
	: mName(name)
	, mStat(stat)
	, mPrice(price) {}

//Copy Constructor
Item::Item(const Item& it) : mName(it.mName), 
mStat(it.mStat), mPrice(it.mPrice) {}

//Get Item Name
std::string Item::getName() {
	return mName;
}

//Get Item stat
int Item::getStat() {
	return mStat;
}

//Get Item Price
int Item::getPrice() {
	return mPrice;
}

//Use item
void Item::use(Character& c) {
	cout << "You used a " << mName << endl;
}

//Swap Two Items
void swap(Item*& lhs, Item*& rhs) {
	Item* temp = lhs;
	lhs = rhs;
	rhs = temp;
}

//Display Item Contents
ostream& operator<<(ostream& os, const Item& it) {
	os << "*******************************************" << endl;
	os << "Item: " << it.mName << endl;
	os << "Stat: " << it.mStat << endl;
	os << "Price: " << it.mPrice << endl;
	os << "*********************************************" << endl;
	return os;
}