#pragma once

#include "Monster.h"

#include <vector>

using namespace std;

class Player: public Character
{
public:
	Player();
	void addInv(shared_ptr<Item>);
	void equip(shared_ptr<Weapon>);
	void equip(shared_ptr<Armor>);
	void dispInv() const;
  int getInventorySize();

	//void drop();

	//void swap(Weapon*);
  void magicAttack(shared_ptr<Character>);

	//void swap(Armor*);
	void useItem();

  Item& getItem(int choice);
  void removeItem();

	void signature(Character*) override;
	void addEXP(int);
	void levelUP();
	shared_ptr<Item>& sellItem(int ind);
	~Player();
  //void printPlayerStats();

  
	void attack(shared_ptr<Character>) override;

	void defend(shared_ptr<Character>) override;

private:
	vector<shared_ptr<Item>> inventory;
	Weapon* ps;	//Sword Pointer
	Armor* pa;	//Armor Pointer
  string mag_move;

	void InvSizeLimit();
	void update();
};

ostream& operator<<(ostream&, Player&);