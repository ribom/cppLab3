#include "creature.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster : public Creature {
	private:
		Item * item;
	public:
		Monster(const string & name, int xpos, int ypos);
		~Monster();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);

};

Monster::Monster(const string & name, int xpos, int ypos) : Creature(name, "Monster", 100, xpos, ypos) {
	item = new Item(20, "Monster armor");
}

bool Monster::pick_up(const Item * item){
	return false;
}


void Monster::go(const int xDir, const int yDir) {
	xpos = xDir;
	ypos = yDir;
}

#endif