#include "Armor.h"

//Constructor
Armor::Armor(std::string name, int defense, int price)
	: Item(name, defense, price) { }

//Copy Constructor
Armor::Armor(const Armor& rhs) :
	Item(rhs.mName, rhs.mStat, rhs.mPrice) {}

//Equip armor --> mods the player's defense to provide them more
void Armor::use(Character& c) {
  c.setDEF(mStat);
  cout << mName << " equipped!" << endl;
}