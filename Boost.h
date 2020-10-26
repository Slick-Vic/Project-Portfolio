#pragma once

#include "Item.h"
using namespace std;

class Boost : public Item {
public:
	Boost(string, int, int, string);
	Boost(const Boost&);

	const string& getTarget() const;

	void use(Character&);

private:
	string mTarget;
};