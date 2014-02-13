#include "creature.h"
#include <fstream>
#include <iostream>

#ifndef PRINCESS_H
#define PRINCESS_H
#define Princess_TYPE "Princess"

using namespace std;

class Princess : public Creature {
	private:
		string story;
		void loadStory();
	public:
		Princess(ifstream & file);
		virtual ~Princess();
		virtual void go(const int xDir, const int yDir);
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);
		virtual void tellStory() const;
		virtual void printBackpack() const;
		virtual bool action(Creature * hero);
		virtual string getType() const;
};


Princess::Princess(ifstream & file) : Creature(file) {
	mapSign[0] = 'P';
}

Princess::~Princess() {}

string Princess::getType() const {
	return Princess_TYPE;
}

bool Princess::action(Creature * hero) {
	show();
	hero->action(this);
	string choice;
	cout << hero->getName() << "! You have found the princess! Do you want to win this game? (y/n): ";
	cin >> choice;
	if(choice != "y") {
		cout << "Well it doesn't really matter what you want at this point.." << endl;
	}
	return true;
}

void Princess::tellStory() const {
	cout << story << endl;
}

void Princess::loadStory() {
	ifstream storyFile;
	string path = "text/npc/" + getName() + ".txt";
	storyFile.open(path);
	if(storyFile.is_open() != true) {
		cout << "Could not find story with path: " << path << endl; 
		return;
	}
	string line;
	while(getline(storyFile, line)) {
		cout << "the line!" << line << endl;
		story += line + "\n";
	}
	storyFile.close();
}

void Princess::go(const int xDir, const int yDir) {}

bool Princess::pick_up(const Item * item) {
	return backpack->addItem(item);
}

bool Princess::fight(Creature * enemy) {
	return true;
}

void Princess::printBackpack() const {
	cout << endl << getName() << "'s has the following items to offer you:" << endl;
	cout << *backpack << endl;
}

#endif