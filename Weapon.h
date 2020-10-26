#pragma once

#include "Item.h"

class Weapon : public Item {
public:
	Weapon(std::string name, int defense, int price);
	Weapon(const Weapon&);

	void use(Character&);
private:
};

