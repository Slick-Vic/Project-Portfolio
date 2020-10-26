#pragma once

#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Character{
public:
	Character(int lvl, int hp, int atk, int def, int matk, int mdef,
	int spd, int money, int exp);

	virtual void attack(shared_ptr<Character>);

	virtual void defend(shared_ptr<Character>);

	virtual void signature(Character*) = 0;

	void setHP(int);
  void resetHP();

	void setATK(int);

  void setMATK(int);

	void setDEF(int);

  void setMDEF(int);

  // DOESN'T increase by default
  void setTEMPDEF(int);

  // DOESN'T increase by default
  void setTEMPMDEF(int);

	void setMONEY(int);

	void setSPD(int);

	void setLVL(int);

	void setEXP(int);

	const string& getName() const;

	map<string, int>& getStatMap();

	int& getStat(const string&);

protected:
	string name, sig_move;							//Player Name
	//int HP, ATK, DEF, MONEY, SPD, LVL, EXP;
	map <string, int> stats;
};