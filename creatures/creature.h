#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include "../item.h"

using namespace std;

class Creature {
	private:
		string name;
		string type;
		int HP;
		
	protected:		
		int xpos;
		int ypos;

	public:
		Creature(const string & name, const string & type, const int & HP, const int & xpos, const int & ypos);
		string getName() const;
		string getType() const;
		int getHP() const;
		virtual void go(const int xDir, const int yDir) = 0; // – gå åt håll
		void fight(Creature & enemy); // – slåss med
		virtual bool pick_up(const Item * item) = 0; // – ta upp sak
		void drop(const Item * item); // – släpp sak på marken
		void talk_to(Creature & npc); // – konversera med
		int getXpos() const;
		int getYpos() const;
};

Creature::Creature(const string & name, const string & type, const int & HP, const int & xpos, const int & ypos) 
	: name(name), type(type), HP(HP), xpos(xpos), ypos(ypos) {}

string Creature::getName() const {
	return name;
}

string Creature::getType() const {
	return type;
}

int Creature::getHP() const {
	return HP;
}

void Creature::fight(Creature & enemy) {

}

void Creature::drop(const Item * item){

}
void Creature::talk_to(Creature & npc) {

}

int Creature::getXpos() const {
	return xpos;
}

int Creature::getYpos() const {
	return ypos;
}

#endif