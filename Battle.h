#pragma once

#include <memory>
#include "Player.h"

class Battle {
public:
	Battle(std::shared_ptr<Player> p, std::shared_ptr<Monster> m);

	bool isPlayersTurn();
	void switchPlayersTurn();

	std::shared_ptr<Player> getPlayer();
	std::shared_ptr<Monster> getMonster();

	void attack();
  void magicAttack();
	void defend();
	void flee();
  void printMonsterStats();

  bool getIsFleeing();

	void monsterMove();

	bool isActive();
	void endBattle(bool);
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Monster> mMonster;
	bool mPlayersTurn;
	bool mActive = true;
  bool isFleeing = false;
};

