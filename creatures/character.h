#include "creature.h"

#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character : public Creature {
	private:
		int position;
	
	public:
		Character(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image);
		virtual ~Character();
		virtual void go(const int xDir, const int yDir);
		virtual bool fight(Creature * enemy);

};

void Character::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

bool Character::fight(Creature * enemy) {
	enemy->show();
	cout << "You need to fight this " << enemy->getType() << "!" << endl;
	cout << "Do you want to use:\n1. Your weapon\n2. Magic\nChoice: ";
	string choice;
	cin >> choice;
	return true;
}

Character::Character(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image) 
	: Creature(name, type, 100, xpos, ypos, image) { //todo fixa så att hero å hp inte är statiska
}

Character::~Character(){};


#endif