#include <iostream>
#include "Gameplay.h"
#include <random>
#include <chrono>
#include <iomanip>
using namespace std::chrono;
using namespace std;


int main() {
  //start the random seed
  srand((unsigned)(time(NULL)));
  //initialize the player
  shared_ptr<Player> player = make_shared<Player>();
  //initialize and run the game
  Gameplay gameplay(player);
  return 0;
}