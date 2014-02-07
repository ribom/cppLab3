#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include "../item.h"
#include "../artdisplayer.h"
#include "../backpack.h"

using namespace std;

class Creature {
	private:
		string name;
		string type;
		int HP;
		Artdisplayer creatureImage;
		
	protected:		
		int xpos;
		int ypos;
		bool mayMove;
		Backpack * backpack;

	public:
		Creature(const string & name, const string & type, const int & HP, const int & xpos, const int & ypos, const Artdisplayer & image);
		~Creature();
		string getName() const;
		string getType() const;
		string getImageName() const;
		Backpack * getBackpack() const;
		int getHP() const;
		virtual void go(const int xDir, const int yDir) = 0; // – gå åt håll
		bool fight(Creature * enemy); // – slåss med
		bool pick_up(const Item * item); // – ta upp sak
		void drop(const Item * item); // – släpp sak på marken
		void talk_to(Creature & npc); // – konversera med
		int getXpos() const;
		int getYpos() const;
		void turnUsed(const bool & used);
		void show() const;
		void printBackpack() const;
};

Creature::Creature(const string & name, const string & type, const int & HP, const int & xpos, const int & ypos, const Artdisplayer & image) 
	: name(name), type(type), HP(HP), creatureImage(image), xpos(xpos), ypos(ypos) {
		mayMove = true;
		backpack = new Backpack();
	}
Creature::~Creature(){}

bool Creature::pick_up(const Item * item) {
	return backpack->addItem(item);
}

Backpack * Creature::getBackpack() const {
	return backpack;
}

string Creature::getName() const {
	return name;
}

string Creature::getType() const {
	return type;
}

string Creature::getImageName() const {
	return creatureImage.getImageName();
}

int Creature::getHP() const {
	return HP;
}

void Creature::show() const {
	cout << creatureImage;
}

void Creature::turnUsed(const bool & used) {
	if(used) {
		mayMove = false;
	}
	else {
		mayMove = true;
	}
}

bool Creature::fight(Creature * enemy) {
	enemy->show();
	cout << "You need to fight this " << enemy->getType() << "!" << endl;
	cout << "Do you want to use:\n1. Your weapon\n2. Magic\nChoice: ";
	string choice;
	cin >> choice;
	return true;
}

void Creature::printBackpack() const {
	cout << "Your backpack contains the following:" << endl;
	cout << *backpack << endl;
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