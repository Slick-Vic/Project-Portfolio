#pragma once
#include <iostream>
#include <memory>
#include "Battle.h"

class BattleView {
public:
  BattleView(std::shared_ptr<Player> p,std::shared_ptr<Monster> m);

  void startBattle();
  void doMonsterMove();  
  void grabUserInput();
  void displayPlayerItemSelection();
  void tryFlee();
  void nextTurn();

  bool isBattleActive();
private:
  std::unique_ptr<Battle> mBattle;
};
