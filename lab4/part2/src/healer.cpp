#include "healer.h"

using namespace std;

Healer::Healer(string name) : Player(name) {
	// nothing to do here
}

void Healer::doAction(Player *target) {
	// TODO
	int HP = (target->getHP() + 75 > target->getMaxHP() ) ? target->getMaxHP() : target->getHP() + 75;
	target->setHP(HP);
}