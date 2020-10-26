#pragma once

#include <vector>
#include <initializer_list>
#include "Player.h"

using namespace std;

class Shopkeeper {
public:
    Shopkeeper(Player&);

    void addToInventory(std::shared_ptr<Item> item);
    void addToInventory(std::initializer_list<shared_ptr<Item>> items);
    void clearInventory();
    void greet();
    int getSelection(int, int);
    void printInventory();
    void buy();
    void sell();
    char checkYNInput();

    std::shared_ptr<Item> getItem(int choice);
    std::shared_ptr<Item> removeItem(int choice);
private:
    Player& mPlayer;
    std::vector<std::shared_ptr<Item>> mInventory;
};