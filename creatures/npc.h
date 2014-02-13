#include "creature.h"
#include <fstream>
#include <iostream>

#ifndef NPC_H
#define NPC_H
#define NPC_TYPE "Npc"

using namespace std;

class Npc : public Creature {
	private:
		string story;
		void loadStory();
	public:
		Npc(ifstream & file);
		virtual ~Npc();
		virtual void go(const int xDir, const int yDir);
		virtual void talk_to(Creature * hero); // – konversera med
		virtual bool pick_up(const Item * item);
		virtual bool fight(Creature * enemy);
		virtual void tellStory() const;
		virtual string sell(Creature * hero);
		virtual string buy(Creature * hero);
		virtual void printBackpack() const;
		virtual bool action(Creature * hero);
		virtual string getType() const;
};


Npc::Npc(ifstream & file) : Creature(file) {
	loadStory();
	mapSign[0] = 'N';
	money = 300;
}

Npc::~Npc() {}

string Npc::getType() const {
	return NPC_TYPE;
}

void Npc::talk_to(Creature * hero) {
	string choice;
	show();
	cout << "Hello there " << hero->getName() << "! Your reputation precedes you, I am " << getName() <<". What can I do for you?" << endl;
	while(choice != "4" && choice != "bye" && choice != "exit") {
		cout << "1. I want to sell stuff to you old man!\n2. I need to buy something!\n3. How did you end up here?\n4. Well you just look creepy, bye..\nChoice: ";
		cin >> choice;
		if(choice == "1" || choice == "sell") {
			choice = sell(hero);
		}
		else if(choice == "2" || choice == "buy") {
			choice = buy(hero);
		}
		else if(choice == "3" || choice == "story") {
			show();
			tellStory();
		}
	}
}

bool Npc::action(Creature * hero) {
	talk_to(hero);

	return true;
}

string Npc::buy(Creature * hero) {
	show();
	cout << "Oh! So you're here to make a purchase! How wonderful, lets see what I have to offer.." << endl;
	string nameOfItem;
	cin.ignore();
	while(nameOfItem != "bye" && nameOfItem != "exit" && nameOfItem != "sell") {
		printBackpack();
		getline(cin, nameOfItem);
		if(backpack->getItemMap()->find(nameOfItem) != backpack->getItemMap()->end()) {
			Item * item = backpack->getItemMap()->at(nameOfItem);
			if(item->getPrice() <= hero->getMoney()) {
				hero->pick_up(item);
				backpack->getItemMap()->erase(nameOfItem);
				hero->transaction(item->getPrice());
				transaction(item->getPrice()*(-1));
				show();
				cout << "Great choice " << hero->getName() << " I have no doubt you'll be happy with your new " << item->getName() << "!" << endl;
				cout << "If you want to make another purchase..";
			}
			else {
				show();
				cout << "Well I'm sorry " << hero->getName() << " but you can't afford this item.." << endl;
			}
		} else {
			show();
			cout << "What's that? I've never heard of such an absurd item!" << endl;
		}
	}
	return nameOfItem;

}

string Npc::sell(Creature * hero) {
	show();
	cout << "Oh! You want to sell me something eh?! So what do you have to offer?" << endl;
	string nameOfItem;
	cin.ignore();
	while(nameOfItem != "bye" && nameOfItem != "exit" && nameOfItem != "sell") {
		hero->printBackpack();
		getline(cin, nameOfItem);
		if(hero->getBackpack()->getItemMap()->find(nameOfItem) != hero->getBackpack()->getItemMap()->end()) {
			Item * item = hero->getBackpack()->getItemMap()->at(nameOfItem);
			if(item->getPrice() <= getMoney()) {
				pick_up(item);
				hero->getBackpack()->getItemMap()->erase(nameOfItem);
				transaction(item->getPrice());
				hero->transaction(item->getPrice()*(-1));
				show();
				cout << "Oh this looks nice " << hero->getName() << " I'll take well care of your " << item->getName() << "!" << endl;
				cout << "Do you want to sell me anything else?" << endl;
			}
			else {
				show();
				cout << "Well I'm sorry " << hero->getName() << " I can't afford this item.." << endl;
			}
		} else {
			show();
			cout << "What's that? I've never heard of such an absurd item!" << endl;
		}
	}
	return nameOfItem;
}

void Npc::tellStory() const {
	cout << story << endl;
}

void Npc::loadStory() {
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

void Npc::go(const int xDir, const int yDir) {}

bool Npc::pick_up(const Item * item) {
	return backpack->addItem(item);
}

bool Npc::fight(Creature * enemy) {
	return true;
}

void Npc::printBackpack() const {
	cout << endl << getName() << "'s has the following items to offer you:" << endl;
	cout << *backpack << endl;
}

#endif