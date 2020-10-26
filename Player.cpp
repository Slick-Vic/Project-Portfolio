#include "Player.h"

using namespace std;

//Player Constructor
Player::Player() : Character(1,100,20,30,20,20,10,0,0),
ps(nullptr), pa(nullptr) {
	//Character signature move
	sig_move = "OMNISLASH";
  mag_move = "SPOOKY POWER";
}

//Add Item to Inventory
void Player::addInv(shared_ptr<Item> item) {
	inventory.push_back(item);

}

void Player::attack(shared_ptr<Character> c) {
  int damage = 0;
  if (stats["ATK"] - (c->getStat("DEF") > 0) / 5) {
    damage = stats["ATK"] - (c->getStat("TEMPDEF")/5);
  }
  if(damage < 0){
    damage = 1;
  }
  
  cout<<"You use " << this->sig_move <<"!"<<endl;
	c->setHP(-damage);
	cout << "Damage: " << damage << endl;
}

void Player::magicAttack(shared_ptr<Character> c) {
  int damage = 0;
  if (stats["MATK"] - (c->getStat("TEMPMDEF") > 0) / 5) {
    damage = stats["MATK"] - (c->getStat("TEMPMDEF")/5);
  }
  if(damage < 0){
    damage = 1;
  }
  
  cout<<"You used  " << this->mag_move <<"!"<<endl;
	c->setHP(-damage);
	cout << "Damage: " << damage << endl;
}

void Player::defend(shared_ptr<Character> c) {
	cout << "YOU DEFEND!" << endl;
	stats["TEMPDEF"] += 10;
  stats["TEMPMDEF"] += 10;
 }


//Equip Weapon
void Player::equip(shared_ptr<Weapon> weap) {
//	Weapon* sps = new Weapon(sw);

	//Check if Player has Weapon equipped
	//If not...
	if (!ps) {
		//Sword gets equipped for use
		//ps = sps;

		//Modify attack stat
		stats["ATK"] += pa->getStat();
		cout << "Sword Equipped!" << endl;
	}
	//Else...
	else {
		//Sword gets put in invenstory
		//cout << "You have a sword equipped. Moving to inventory..." << endl;

		//Checks if Inventory limit was hit
		try {
			InvSizeLimit();

			inventory.push_back(weap);
		}
		catch (const logic_error& e) {
			cerr << e.what() << endl;
		}
	}
}

//Equip Armor
void Player::equip(shared_ptr<Armor> armor) {
	//Armor* apa = new Armor(ar);

	//Check if Player has Armor equipped
	//If not...
	if (!pa) {
		//Armor gets equipped for use
	//	pa = apa;

		//Modify defense stat
		stats["DEF"] += pa->getStat();
		cout << "Sword Equipped!" << endl;
	}
	//Else...
	else {
		//Sword gets put in invenstory
		cout << "You have a sword equipped. Moving to inventory..." << endl;

		//Checks if Inventory limit was hit
		try {
			InvSizeLimit();
			inventory.push_back(armor);
		}
		catch (const logic_error& e) {
			cerr << e.what() << endl;
		}
	}
}

//Display Inventory
void Player::dispInv() const {

	//Checks if inventory is empty or not
	if (!inventory.empty()) {
		cout << " Inventory:" << endl;
		for (size_t i = 0; i < inventory.size(); ++i) {
			cout << i + 1 << ". " << *inventory[i] << endl;
		}
	}
	//if empty..
	else {
		cout << "There is nothing in your inventory..." << endl;
	}
}

//Use Item in Inventory
void Player::useItem() {
	dispInv();

	int choice;

	//If inventory not empty...
	if (!inventory.empty()) {
		//Throws error if inventory choice is invalid
		try {
			cout << "Select an item: ";
			cin >> choice;
        if(cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
          return;
        }


			if (choice > inventory.size() || choice < 0) {
				throw out_of_range("Invalid choice!");
			}

			choice -= 1;

			// //Use item
      inventory[choice]->use(*this);
      
			//Get rid of item in inventory
			inventory.erase(inventory.begin() + choice);
		}
		catch (const out_of_range& e) {
			cerr << e.what() << endl;
		}
	}
	else {
		return;
	}
}

//Get item at index
Item& Player::getItem(int choice) {
  try{
    if (choice < inventory.size() + 1 && choice > 0){
      return *inventory[choice - 1];
    }
    else{
      throw invalid_argument("Invalid argument for selection...");
    }
  }
  catch(const invalid_argument& e){
    cerr << e.what() << endl;
  }
}

//Use signature move
void Player::signature(Character* c) {
	cout << "SIGNATURE MOVE: " << sig_move << endl;
	c->setHP(-2 * stats["ATK"]);
	cout << "Damage: " << 2 * stats["ATK"] << endl;
}

//Add EXP
void Player::addEXP(int n) {
	stats["EXP"] += n;

	//Check if Player Leveled UP
	levelUP();
}

//Adjust Stats when Player gains a level
void Player::levelUP() {
  cout<<endl;
	//Loop through until EXP < LVL * 100
	while (stats["EXP"] >= stats["LVL"] * 100) {
		cout << "LEVEL UP!" << endl;
		stats["EXP"] -= stats["LVL"] * 100;

		//Update Player Stats
		update();
	}
  cout<<endl;
}

//Update Player stats using RNG
void Player::update() {
	int r1 = 5 + (rand() & 6);
	int r2 = 5 + (rand() & 6);
	int r3 = 5 + (rand() & 6);
	int r4 = 5 + (rand() & 6);
	stats["MAXHP"] += r1;
  stats["HP"] += r1;
	stats["ATK"] += r2;
	stats["DEF"] += r3;
	stats["SPD"] += r4;
	stats["LVL"] += 1;

	//Display New Stats
	cout << "Level = " << stats["LVL"] << endl;
	cout << "MAX HP +" << r1 << endl;
	cout << "ATK +" << r2 << endl;
	cout << "DEF +" << r3 << endl;
	cout << "SPD +" << r4 << endl;
}

//Sell Item in inventory
shared_ptr<Item>& Player::sellItem(int ind) {
  ind--;

	shared_ptr<Item>& item = inventory[ind];
	return item;
}

//Checks if Inventory did not exceed 10 items
void Player::InvSizeLimit() {
	if (inventory.size() == 10) {
		throw logic_error("Inventory Full!");
	}
}

int Player::getInventorySize() {
  return inventory.size();
}

//Display Player information
ostream& operator<<(ostream& os, Player& p) {
	cout << "LEVEL " << p.getStat("LVL") << endl;
	cout << "HEALTH: " << p.getStat("HP")<< "/" <<p.getStat("MAXHP") << endl;
  cout << "ATTACK: " << p.getStat("ATK") << endl;
	cout << "DEFENSE: " << p.getStat("DEF") << endl;
	cout << "SPEED: " << p.getStat("SPD") << endl;
	cout << "EXP: " << p.getStat("EXP") <<endl;
  cout << "PUMPKIN SEEDS: " << p.getStat("MONEY") << endl;

	return os;
}

// void Player::printPlayerStats(){
//   cout << "LEVEL " << this->getStat("LVL") << endl;
// 	cout << "HEALTH: " << this->getStat("HP")<< "/" <<this->getStat("MAXHP") << endl;
//   cout << "ATTACK: " << this->getStat("ATK") << endl;
// 	cout << "DEFENSE: " << this->getStat("DEF") << endl;
// 	cout << "SPEED: " << this->getStat("SPD") << endl;
// 	cout << "EXP: " << this->getStat("EXP") <<endl;
//   cout << "PUMPKIN SEEDS: " << this->getStat("MONEY") << endl;

// }

//Destructor
Player::~Player() {
	if (ps) {
		delete ps;
		ps = nullptr;
	}
	if (pa) {
		delete pa;
		pa = nullptr;
	}

	inventory.clear();
}