#include "Weapon.h"

//Constructor
Weapon::Weapon(std::string name, int attack, int price)
	: Item(name, attack, price) { }

//Copy Constructor
Weapon::Weapon(const Weapon& rhs) :
	Item(rhs.mName, rhs.mStat, rhs.mPrice) {}

//Use Weapon
void Weapon::use(Character& c) {
	// cout << "Cannot use weapon. Must first equip..." << endl;
  c.setATK(mStat);
  cout << mName << " equipped!"<<endl;
}