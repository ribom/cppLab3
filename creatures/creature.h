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

	public:
		Creature(const string & name, const string & type, const int & HP);
		string getName() const;
		string getType() const;
		int getHP() const;
		void go(const int way); // – gå åt håll
		void fight(Creature & enemy); // – slåss med
		void pick_up(const Item &); // – ta upp sak
		void drop(const Item &); // – släpp sak på marken
		void talk_to(Creature & npc); // – konversera med
};

Creature::Creature(const string & name, const string & type, const int & HP) : name(name), type(type), HP(HP) {}

string Creature::getName() const {
	return name;
}

string Creature::getType() const {
	return type;
}

int Creature::getHP() const {
	return HP;
}

void Creature::go(const int way) {

}
void Creature::fight(Creature & enemy) {

}
void Creature::pick_up(const Item &) {

}
void Creature::drop(const Item &){

}
void Creature::talk_to(Creature & npc) {

}

#endif