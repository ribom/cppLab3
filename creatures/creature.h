#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include "../item.h"
#include "../artdisplayer.h"
#include "../backpack.h"
#include "../object.h"

using namespace std;

class Creature {
	private:
		string name;
		string type;
		int HP, maxHP;
		Artdisplayer * creatureImage;
		
	protected:		
		int xpos;
		int ypos;
		bool mayMove;
		Backpack * backpack;
		int money;
		char mapSign[1];

	public:
		Creature(ifstream & file);
		Creature(const string & name);
		virtual ~Creature();
		string getName() const;
		virtual string getType() const {return "Failll!!!!!";}
		string getImageName() const;
		int getMoney() const;
		void transaction(const int & priceOfItem);
		Backpack * getBackpack() const;
		int getHP() const;
		virtual void go(const int xDir, const int yDir) = 0; // – gå åt håll
		virtual bool fight(Creature * enemy) = 0; // – slåss med
		virtual bool action(Creature * enemy) = 0;
		virtual void tellStory() const;
		virtual string sell(Creature * hero) {return NULL;}
		virtual string buy(Creature * hero) {return NULL;}
		bool pick_up(const Item * item); // – ta upp sak
		void drop(const Item * item); // – släpp sak på marken
		virtual void talk_to(Creature * npc); // – konversera med
		int getXpos() const;
		int getYpos() const;
		void turnUsed(const bool & used);
		void show() const;
		bool dead() const;
		virtual void printBackpack() const = 0;
		bool tryUnlockObject(Object * object);
		void saveToFile(ofstream & saveFile);
		char getMapSign() const;
};

Creature::Creature(ifstream & file) {
	HP = 100;
	maxHP = 100;
	mayMove = true;
	money = 60;
	backpack = new Backpack();
	type = this->getType();
	getline(file, name);

	string line;
	getline(file, line);
	ypos = atoi(line.c_str());
	getline(file, line);
	xpos = atoi(line.c_str());

	getline(file, line);
	string image = "creatures/" + line;
	creatureImage = new Artdisplayer(image);

	while(getline(file, line) && line == "item") {
		getline(file, line);
		this->pick_up(new Item(file, line));
	}
}

Creature::Creature(const string & name) : name(name), type("Hero"), HP(100), maxHP(100), xpos(10), ypos(18), mayMove(true) {
		creatureImage = new Artdisplayer("creatures/hero");
		backpack = new Backpack();
		money = 60;
}

char Creature::getMapSign() const {
	return mapSign[0];
}

Creature::~Creature(){
	delete backpack;
	delete creatureImage;
}

bool Creature::dead() const {
	if(HP <= 0) {
		return true;
	}
	return false;
}

bool Creature::tryUnlockObject(Object * object) {
	string command;
	object->show();
	cout << "This is the " << object->getName() << ". To unlock this you need to use " << object->getKey() << "." << endl;
	cout << "Do you want to use this item to unlock " << object->getName()  << "? (y/n): ";
	cin >> command;
	if(command == "y") {
		if(backpack->getItemMap()->find(object->getKey()) != backpack->getItemMap()->end()) {
			return object->unlock(object->getKey());
		}	
	}
	return false;
}

void Creature::saveToFile(ofstream & saveFile) {
	saveFile << "creatures" << endl << getType() << endl << getName() << endl << getYpos() << endl << getXpos() << endl << getImageName() << endl;
}

bool Creature::pick_up(const Item * item) {
	return backpack->addItem(item);
}

void Creature::tellStory() const {}

Backpack * Creature::getBackpack() const {
	return backpack;
}

string Creature::getName() const {
	return name;
}

string Creature::getImageName() const {
	return creatureImage->getImageName();
}

int Creature::getMoney() const {
	return money;
}
void Creature::transaction(const int & priceOfItem) {
	money -= priceOfItem;
}

int Creature::getHP() const {
	return HP;
}

void Creature::show() const {
	cout << *creatureImage;
}

void Creature::turnUsed(const bool & used) {
	if(used) {
		mayMove = false;
	}
	else {
		mayMove = true;
	}
}

void Creature::drop(const Item * item){

}
void Creature::talk_to(Creature * npc) {}

int Creature::getXpos() const {
	return xpos;
}

int Creature::getYpos() const {
	return ypos;
}

#endif