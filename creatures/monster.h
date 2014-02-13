#include "creature.h"

#ifndef MONSTER_H
#define MONSTER_H

#define MONSTER_TYPE "Monster"

class Monster : public Creature {
	public:
		Monster(ifstream & file);
		virtual ~Monster();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);
		virtual void printBackpack() const;
		virtual bool action(Creature * enemy);
		virtual string getType() const;

};

Monster::Monster(ifstream & file) : Creature(file) {
	mapSign[0] = 'M';
}

Monster::~Monster(){}

string Monster::getType() const {
	return MONSTER_TYPE;
}

bool Monster::action(Creature * enemy) {
	return fight(enemy);
}

bool Monster::pick_up(const Item * item){
	return false;
}

void Monster::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

bool Monster::fight(Creature * enemy) {
	show();
	cout << "You need to fight this " << getType() << "!" << endl;
	cout << "Do you want to use:\n1. Your weapon\n2. Magic\nChoice: ";
	string choice;
	cin >> choice;

	return false;
}

void Monster::printBackpack() const {
	cout << "The " << getType() << " carried the following items: " << endl << *backpack << endl;
}

#endif