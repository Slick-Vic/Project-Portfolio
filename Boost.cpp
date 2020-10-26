#include "Boost.h"

//Constructor
Boost::Boost(std::string name, int boost, int price, string target)
	: Item(name, boost, price), mTarget(target) {}

//Copy Constructor
Boost::Boost(const Boost& b) : 
	Item(b.mName, b.mPrice, b.mStat), mTarget(b.mTarget) {}

//Get Boost TYPE
const string& Boost::getTarget() const {
	return mTarget;
}

//Use Boost Item
void Boost::use(Character& c) {
	Item::use(c);
	c.getStat(mTarget) += mStat;
}