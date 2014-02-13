#include "creature.h"

#ifndef DRAGON_H
#define DRAGON_H

#define Dragon_TYPE "Dragon"

class Dragon : public Creature {
	public:
		Dragon(ifstream & file);
		virtual ~Dragon();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);
		virtual void printBackpack() const;
		virtual bool action(Creature * enemy);
		virtual string getType() const;

};

Dragon::Dragon(ifstream & file) : Creature(file) {
	mapSign[0] = 'D';
}

Dragon::~Dragon(){}

string Dragon::getType() const {
	return Dragon_TYPE;
}

bool Dragon::action(Creature * enemy) {
	return fight(enemy);
}

bool Dragon::pick_up(const Item * item){
	return false;
}

void Dragon::go(const int xDir, const int yDir) {}

bool Dragon::fight(Creature * enemy) {
	show();
	cout << "You need to fight this " << getType() << "!" << endl;
	cout << "To kill it you need a Black Arrow! Do you have this item? (y/n): ";
	string choice;
	cin >> choice;
	if(choice == "y") {
		for(auto it : *(enemy->getBackpack()->getItemMap())) {
			if(it.second->getName() == "Black Arrow") {
				return false;
			}
		}
	}

	return true;
}

void Dragon::printBackpack() const {
	cout << "The " << getType() << " carried the following items: " << endl << *backpack << endl;
}

#endif