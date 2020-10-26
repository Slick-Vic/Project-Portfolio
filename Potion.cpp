#include "Potion.h"
#include <iostream>

//Constructor
Potion::Potion(std::string name, int healing, int price)
	: Item(name, healing, price) { }

//Copy Constructor
Potion::Potion(const Potion& rhs) :
	Item(rhs.mName, rhs.mStat, rhs.mPrice) {}

//Use Potion
void Potion::use(Character& c) {
  std::cout<< "Using Potion..." << std::endl;
	//Item::use(c);

  if (c.getStat("HP") + mStat >= c.getStat("MAXHP")) {
    c.resetHP();
  } else {
    c.setHP(mStat);
  } 
}