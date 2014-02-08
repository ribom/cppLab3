#include "creature.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster : public Creature {
	public:
		Monster(const string & name, const string & type, int xpos, int ypos, const Artdisplayer & image);
		virtual ~Monster();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);

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

bool Monster::fight(Creature * enemy) {
	return true;
}

#endif