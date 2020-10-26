#include "Character.h"

//Constructor
Character::Character(int lvl, int hp, int atk, int def, int matk, int mdef,
	int spd, int money, int exp) {
	//Add stats to stat map
	stats["LVL"] = lvl;
	stats["HP"] = hp;
	stats["MAXHP"] = hp;
	stats["ATK"] = atk;
  stats["MATK"] = matk;
	stats["DEF"] = def;
  stats["TEMPDEF"] = def;
  stats["MDEF"] = mdef;
  stats["TEMPMDEF"] = mdef;
	stats["SPD"] = spd;
	stats["MONEY"] = money;
	stats["EXP"] = exp;
}

//Character attack each other => attacked Character loses HP
void Character::attack(shared_ptr<Character> c) {
	c->stats["HP"] -= stats["ATK"];
	cout << "Damage: " << stats["ATK"] << endl;
}

//Character defends against an attack
void Character::defend(shared_ptr<Character> c) {
	// cout << "DEFEND!" << endl;
	// stats["HP"] += (stats["DEF"] - c->stats["ATK"]);
	// cout << "Monster Damage: " << -stats["DEF"] + c->stats["ATK"] << endl;
}

//HP Setter
void Character::setHP(int amt){
	stats["HP"] += amt;
}

void Character::resetHP() {
  stats["HP"] = stats["MAXHP"];
}

//ATK Setter
void Character::setATK(int amt) {
	stats["ATK"] += amt;
}

//MATK Setter
void Character::setMATK(int amt) {
	stats["MATK"] += amt;
}

//MONEY Setter
void Character::setMONEY(int amt) {
	stats["MONEY"] += amt;
}

//DEF Setter
void Character::setDEF(int amt) {
	stats["DEF"] += amt;
}

//TEMPDEF Setter, DOESN'T increase by default
void Character::setTEMPDEF(int amt) {
	stats["TEMPDEF"] = amt;
}

//TEMPDEF Setter, DOESN'T increase by default
void Character::setTEMPMDEF(int amt) {
	stats["TEMPMDEF"] = amt;
}

//SPD Setter
void Character::setSPD(int amt) {
	stats["SPD"] += amt;
}

//LVL Setter
void Character::setLVL(int amt) {
	stats["LVL"] += amt;
}

//EXP Setter
void Character::setEXP(int amt) {
	stats["EXP"] += amt;
}

//Name Getter
const string& Character::getName() const {
	return name;
}

//Get Map Object of Stats
map<string, int>& Character::getStatMap() {
	return stats;
}

//Get Individual Stat Value
int& Character::getStat(const string& s) {
	//Checks if valid stat is entered
	try {
		return stats[s];
	}
	catch (const invalid_argument& e) {
		cerr << "Invalid argument entered for stat." << endl;
	}

}