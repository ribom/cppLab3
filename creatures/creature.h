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
		int money;

	public:
		Creature(const string & name, const string & type, const int & HP, const int & xpos, const int & ypos, const Artdisplayer & image);
		virtual ~Creature();
		string getName() const;
		string getType() const;
		string getImageName() const;
		int getMoney() const;
		void transaction(const int & priceOfItem);
		Backpack * getBackpack() const;
		int getHP() const;
		virtual void go(const int xDir, const int yDir) = 0; // – gå åt håll
		virtual bool fight(Creature * enemy) = 0; // – slåss med
		virtual void tellStory() const;
		virtual string sell(Creature * hero) {return NULL;}
		virtual string buy(Creature * hero) {return NULL;}
		bool pick_up(const Item * item); // – ta upp sak
		void drop(const Item * item); // – släpp sak på marken
		void talk_to(Creature * npc); // – konversera med
		int getXpos() const;
		int getYpos() const;
		void turnUsed(const bool & used);
		void show() const;
		virtual void printBackpack() const = 0;
};

Creature::Creature(const string & name, const string & type, const int & HP, const int & xpos, const int & ypos, const Artdisplayer & image) 
	: name(name), type(type), HP(HP), creatureImage(image), xpos(xpos), ypos(ypos), money(50) {
		mayMove = true;
		backpack = new Backpack();
	}
Creature::~Creature(){
	delete backpack;
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

string Creature::getType() const {
	return type;
}

string Creature::getImageName() const {
	return creatureImage.getImageName();
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

void Creature::drop(const Item * item){

}
void Creature::talk_to(Creature * npc) {
	string choice;
	npc->show();
	cout << "Hello there " << name << "! Your reputation precedes you, I am " << npc->getName() <<". What can I do for you?" << endl;
	while(choice != "4" && choice != "bye" && choice != "exit") {
		cout << "1. I want to sell stuff to you old man!\n2. I need to buy something!\n3. How did you end up here?\n4. Well you just look creepy, bye..\nChoice: ";
		cin >> choice;
		if(choice == "1" || choice == "sell") {
			choice = npc->sell(this);
		}
		else if(choice == "2" || choice == "buy") {
			choice = npc->buy(this);
		}
		else if(choice == "3" || choice == "story") {
			npc->show();
			npc->tellStory();
		}
	}
}

int Creature::getXpos() const {
	return xpos;
}

int Creature::getYpos() const {
	return ypos;
}

#endif