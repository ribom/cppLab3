#include "creature.h"

#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character : public Creature {
	private:
		int position;
	
	public:
		Character(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image);
		~Character();
		virtual bool pick_up(const Item * item);
		virtual void go(const int xDir, const int yDir);

};

void Character::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

Character::Character(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image) 
	: Creature(name, type, 100, xpos, ypos, image) { //todo fixa så att hero å hp inte är statiska
}

Character::~Character(){};

bool Character::pick_up(const Item * item) {
	return backpack.addItem(item);
}

#endif