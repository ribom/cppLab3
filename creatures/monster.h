#include "creature.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster : public Creature {
	private:
		Item * item;
	public:
		Monster(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image);
		~Monster();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);

};

Monster::Monster(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image) 
	: Creature(name, type, 100, xpos, ypos, image) {
	//item = new Item(20, "Monster armor");
}

Monster::~Monster(){}

bool Monster::pick_up(const Item * item){
	return false;
}


void Monster::go(const int xDir, const int yDir) {
	if(mayMove) {
		xpos = xDir;
		ypos = yDir;
	}
}

#endif