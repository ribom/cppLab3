#include "creature.h"

#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_TYPE "Hero"

using namespace std;

class Character : public Creature {
	private:
		bool winner;
	
	public:
		Character(ifstream & file);
		Character(const string & name);
		virtual ~Character();
		virtual void go(const int xDir, const int yDir);
		virtual bool fight(Creature * enemy);
		virtual void printBackpack() const;
		virtual bool action(Creature * enemy);
		virtual string getType() const;

};

Character::Character(ifstream & file) : Creature(file) {
	mapSign[0] = 'H';
	winner = false;
}

Character::Character(const string & name) : Creature(name) {
	mapSign[0] = 'H';
	winner = false;
}

Character::~Character(){};

string Character::getType() const {
	return CHARACTER_TYPE;
}

bool Character::action(Creature * creature) {
	if(creature->getType() == "Princess") {
		winner = true;
	}

	return winner;
}

void Character::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

bool Character::fight(Creature * enemy) {
	return true;
}

void Character::printBackpack() const {
	cout << "\nYour backpack contains the following:" << endl;
	cout << *backpack << endl;
}

#endif