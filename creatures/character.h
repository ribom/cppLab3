#include "creature.h"
#include "../backpack.h"

#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character : public Creature {
	private:
		Backpack backpack;
		int position;
	
	public:
		Character(const string & name, int xpos, int ypos);
		~Character();

		void printBackpack() const;
};

Character::Character(const string & name, int xpos, int ypos) : Creature(name, "Hero", 100, xpos, ypos) { //todo fixa så att hero å hp inte är statiska
	Item * startingArmor = new Item(5, "Leather armor");
	backpack.addItem(startingArmor);
}

Character::~Character(){};

void Character::printBackpack() const {
	cout << "Your backpack contains the following:" << endl;
	cout << backpack << endl;
}

#endif