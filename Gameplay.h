#pragma once

#include "Battle.h"
#include "BattleView.h"
#include "Shopkeeper.h"
#include "Map.h"

#include <ctime>
#include <limits>
#include <chrono>
#include <thread>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace chrono;
using namespace std;

class Gameplay {
public:
    Gameplay(shared_ptr<Player>);

    void gameplayLoop();

    void healerEncounter();

    void menu(Shopkeeper& s);

    void printChest();

    void goOnDate();

    void printZero();

    void witchEncounter();

    void initializeFight(int monsterLevel);

    ~Gameplay();
private:
    Map* mp;
    shared_ptr<Player> player;
    bool beatLock = false;
    bool beatOB = false;
    bool witchEvent = false;
    bool end = false;

    vector<int> midTierMonster = { 6,7,8 };
    vector<int> lowTierMonster = { 3,4,5 };

    void searchForest();

    void checkYNInput(string&);
};

