#include "creature.h"

#ifndef BAT_H
#define BAT_H

#define Bat_TYPE "Bat"

class Bat : public Creature {
	public:
		Bat(ifstream & file);
		virtual ~Bat();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);
		virtual void printBackpack() const;
		virtual bool action(Creature * enemy);
		virtual string getType() const;

};

Bat::Bat(ifstream & file) : Creature(file) {
	mapSign[0] = 'M';
}

Bat::~Bat(){}

string Bat::getType() const {
	return Bat_TYPE;
}

bool Bat::action(Creature * enemy) {
	return fight(enemy);
}

bool Bat::pick_up(const Item * item){
	return false;
}

void Bat::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

bool Bat::fight(Creature * enemy) {
	show();
	cout << "You need to fight this " << getType() << "!" << endl;
	cout << "Do you want to use:\n1. Your weapon\n2. Magic\nChoice: ";
	string choice;
	cin >> choice;

	return false;
}

void Bat::printBackpack() const {
	cout << "The " << getType() << " carried the following items: " << endl << *backpack << endl;
}

#endif