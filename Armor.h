#pragma once

#include "Item.h"

class Armor : public Item {
public:
	Armor(std::string name, int defense, int price);
	Armor(const Armor&);

	void use(Character&);
private:
};
