#include "BattleView.h"

//Battle constructor --> takes in a player and a monster
BattleView::BattleView(std::shared_ptr<Player> p,std::shared_ptr<Monster> m) {
  mBattle = std::make_unique<Battle>(p, m);
};

//initializes the battle
void BattleView::startBattle() {
  //displays the monster's name and the monster's ascii art if it exists
    std::cout << mBattle->getMonster()->getName() << " appeared!" << std::endl;
    if(mBattle->getMonster()->getMonsterASCII() != ""){
      cout<<mBattle->getMonster()->getMonsterASCII()<<endl;

    }
    //setting the temp defenses of the monster and player for use when they defend against an attack
    mBattle->getPlayer()->setTEMPDEF(mBattle->getPlayer()->getStat("DEF"));
    mBattle->getPlayer()->setTEMPMDEF(mBattle->getPlayer()->getStat("MDEF"));
    mBattle->getMonster()->setTEMPDEF(mBattle->getMonster()->getStat("DEF"));
    mBattle->getMonster()->setTEMPMDEF(mBattle->getMonster()->getStat("MDEF"));
    //player's turn
    if (mBattle->isPlayersTurn()) {
        do {
          //reset defenses if they used defend on the last round
            mBattle->getPlayer()->setTEMPDEF(
              mBattle->getPlayer()->getStat("DEF")
            );
            mBattle->getPlayer()->setTEMPMDEF(
              mBattle->getPlayer()->getStat("MDEF")
            );
            
            mBattle->getMonster()->setTEMPDEF(
              mBattle->getMonster()->getStat("DEF")
            );

            mBattle->getMonster()->setTEMPMDEF(
              mBattle->getMonster()->getStat("MDEF")
            );
            //gets the user's input
            grabUserInput();
            //if the battle is still active at the end, do the monster's move
            if (mBattle->isActive()) doMonsterMove();
        } while(mBattle->isActive());
        //if the player flees successfully it is still their turn so they do not lose, just escape
       mBattle->endBattle(mBattle->getIsFleeing());
    }
    else {
        do {
            mBattle->getPlayer()->setTEMPDEF(mBattle->getPlayer()->getStat("DEF"));
            mBattle->getPlayer()->setTEMPDEF(mBattle->getPlayer()->getStat("MDEF"));
            mBattle->getMonster()->setTEMPDEF(mBattle->getMonster()->getStat("DEF"));
            mBattle->getMonster()->setTEMPDEF(mBattle->getMonster()->getStat("MDEF"));
            doMonsterMove();

             if (mBattle->isActive()) grabUserInput();
        } while(mBattle->isActive());
          mBattle->endBattle(mBattle->getIsFleeing());
    }
}
//do the monster's move
void BattleView::doMonsterMove() {
  mBattle->monsterMove();
}

//gets the user input
void BattleView::grabUserInput() {
  cout<<endl;
  //displays the user's HP
  cout<<"Your current HP: " <<mBattle->getPlayer()->getStat("HP")<<endl;
    if(mBattle->getMonster()->getStat("HP") <= 0){
      cout<<"Your opponent's HP is 0"<<endl;
  }else{
      cout<<"Your opponent's HP: " <<mBattle->getMonster()->getStat("HP")<<endl;
   }
  cout<<endl;

  char input;
  bool inputValid = true;
  std::cout << "Your turn!" << std::endl;

  do {
    std::cout << "Would you like to (A)ttack, (M)agic Attack, (D)efend, use an (I)tem, (F)lee or (P)eek monster stats?" << std::endl;

    std::cin >> input;

    switch (input) {
      //regular attack
      case 'A':
        inputValid = true;
        mBattle->attack();
        break;
        //magic attack
      case 'M':
        inputValid = true;
        mBattle->magicAttack();
        break;
        //defend
      case 'D':
        inputValid = true;
        mBattle->defend();
        break;
        //use an item
      case 'I':
        inputValid = true;
        displayPlayerItemSelection();
        break;
        //attempt to flee
      case 'F':
        inputValid = true;
        tryFlee();
        break;
        //peek at the monster's stats
      case 'P':
        inputValid = true;
        mBattle->printMonsterStats();
        break;
      default:
        inputValid = false;
        break;
    }
  } while (inputValid == false);


}
//displays the player's items
void BattleView::displayPlayerItemSelection() {
  mBattle->getPlayer()->useItem();
  mBattle->switchPlayersTurn();
}
//attempt to flee
void BattleView::tryFlee() {
  mBattle->flee();
}
//returns true if neither player has died yet
bool BattleView::isBattleActive() {
    return mBattle->isActive();
}
//switches the players turns
void BattleView::nextTurn() {
  mBattle->switchPlayersTurn();
}