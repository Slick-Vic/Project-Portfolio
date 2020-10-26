#include "Battle.h"

//Constructor
Battle::Battle(std::shared_ptr<Player> p, std::shared_ptr<Monster> m)
	: mPlayer(p)
	, mMonster(m) {
	
  //Decides who goes first
	//If Player speed > Monster speed, Player goes first (true) else second (false)
	mPlayersTurn = p->getStat("SPD") > m->getStat("SPD");
}

//Checks if Player Turn...true => yes
bool Battle::isPlayersTurn() {
	return mPlayersTurn;
}

//Switch Turns based on bool value mPlayerTurn
void Battle::switchPlayersTurn() {
	mPlayersTurn = !mPlayersTurn;
}

//Get Player Pointer
std::shared_ptr<Player> Battle::getPlayer() {
	return mPlayer;
}

//Get Monster Pointer
std::shared_ptr<Monster> Battle::getMonster() {
	return mMonster;
}

//Player and Monster Attack Each Other
void Battle::attack() {
	isPlayersTurn() ? mPlayer->attack(mMonster) : mMonster->attack(mPlayer);
	switchPlayersTurn();
}

//Player and Monster Attack Each Other
void Battle::magicAttack() {
	mPlayer->magicAttack(mMonster);
	switchPlayersTurn();
}

//Player and Monster Defend Against Each Other
void Battle::defend() {
	isPlayersTurn() ? mPlayer->defend(mMonster) : mMonster->defend(mPlayer);
	switchPlayersTurn();
}
bool Battle::getIsFleeing(){
  return isFleeing;
}
//Flee a battle --> random chance 50/50 chance
void Battle::flee() {
	int coin = rand() % 2; //Heads or Tails

	//Heads => Escaped from battle
	if (coin == 1) {
		std::cout << "You escaped!" << std::endl;
    mActive = false;
    isFleeing = true;
	}
	//Tails => Could not Escape
	else {
		std::cout << "Couldn't escape!" << std::endl;
    switchPlayersTurn();
	}
}

//Allows the player to view the monster's stats --> know if there is a type advantage physical vs magic
void Battle::printMonsterStats() {
  mMonster->printMonsterStats();
  switchPlayersTurn();
}

//Checks if both Player and Monster are Alive
bool Battle::isActive() {
  // if battle is not currently set to active because user fleed
	if (!mActive) {
    return mActive; // return false
  } else {
    mActive = (mPlayer->getStat("HP") > 0) && (mMonster->getStat("HP") > 0);
    //if monster AND player health is greater than 0
    return mActive; //return true
  }
}

//If Monster HP < 10% => Monster starts to defend itself
void Battle::monsterMove() {
	(mMonster->getStat("HP") > (mMonster->getStat("HP") * 0.1)) ? attack() : defend();
}

// Take care of stat changes at end of battle
void Battle::endBattle(bool isFleed) {
  mActive = false;
  getPlayer()->setTEMPDEF(
    getPlayer()->getStat("DEF")
    );

  //if it wasn't the player's turn when the combat ended it indicates that the player has won
	if (!mPlayersTurn) {
		// Increase player's exp
		std::cout << "You win!" << std::endl;
    //player gains the monster's experience offering
		std::cout << "You gained " << mMonster->getStat("EXP") << " experience points!" << std::endl;
		mPlayer->addEXP(mMonster->getStat("EXP"));
    cout<<endl;
  

		// Player makes money
		mPlayer->getStat("MONEY") += mMonster->getStat("MONEY");
		std::cout << "You gained " << mMonster->getStat("MONEY") << " pumpkin seeds!" << std::endl;
    //if the monster is a mimic, they have no items
  if(mMonster->getName() != "Mimic"){
    // 	// Player gets monster's item
    //else, they only have a chance of dropping their item --> lock, shock, and barrel MUST drop their item to use against Oogie Boogie
    int didDrop = rand() % 3;
    if (didDrop >= 2 || mMonster->getName() == "Lock, Shock and Barrel")
  {
      mPlayer->addInv(mMonster->getItem());
		std::cout << "The enemy dropped a " << mMonster->getItem()->getName() << "!" << std::endl;   
  }

  }
	}
	else {
    if (isFleed) {
      return;
    }else{
      // Player loses half their money
      int moneyLost = mPlayer->getStat("MONEY") / 2;
      std::cout << "You lost..." << std::endl;
      std::cout << "You dropped " << moneyLost << " pumpkin seeds..." << std::endl;
      mPlayer->setMONEY(-moneyLost);
      //sets HP back to maxHP if they lost
      int currentHP = mPlayer->getStat("HP");
      currentHP *= -1;
      mPlayer->setHP(
        mPlayer->getStat("MAXHP") + currentHP);
      }
    }
	}
