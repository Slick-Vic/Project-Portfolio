#pragma once

#include "Character.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Boost.h"

using namespace std;

class Item;

class Monster : public Character
{
public:
	Monster(int);

	void signature(Character*) override;

	shared_ptr<Item> getItem();

	virtual void attack(shared_ptr<Character>) override;

	virtual void defend(shared_ptr<Character>) override;
  void printMonsterStats();
  string getMonsterASCII();
  Monster getMidTierMonster();
protected:
  shared_ptr<Item> mItem;
  string monsterASCII = "";
};

ostream& operator<<(ostream&, Monster*);