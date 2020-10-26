#pragma once

#include "Item.h"

class Potion : public Item {
public:
	Potion(std::string name, int healing, int price);
	Potion(const Potion&);

	void use(Character&);
private:
};

