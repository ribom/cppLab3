#include "creature.h"

#ifndef TREX_H
#define TREX_H

#define Trex_TYPE "Trex"

class Trex : public Creature {
	public:
		Trex(ifstream & file);
		virtual ~Trex();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);
		virtual void printBackpack() const;
		virtual bool action(Creature * enemy);
		virtual string getType() const;

};

Trex::Trex(ifstream & file) : Creature(file) {
	mapSign[0] = 'M';
}

Trex::~Trex(){}

string Trex::getType() const {
	return Trex_TYPE;
}

bool Trex::action(Creature * enemy) {
	return fight(enemy);
}

bool Trex::pick_up(const Item * item){
	return false;
}

void Trex::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

bool Trex::fight(Creature * enemy) {
	show();
	cout << "You need to fight this " << getType() << "!" << endl;
	cout << "Do you want to use:\n1. Your weapon\n2. Magic\nChoice: ";
	string choice;
	cin >> choice;

	return false;
}

void Trex::printBackpack() const {
	cout << "The " << getType() << " carried the following items: " << endl << *backpack << endl;
}

#endif