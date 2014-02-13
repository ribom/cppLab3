#include <iostream>
#include <iomanip>
#include "artdisplayer.h"
#include <fstream>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item {
	private:
		int weight, xpos, ypos, price;
		string name;
		Artdisplayer * itemImage;

	public:
		Item(ifstream & itemFile, string & line);
		~Item();
		int getWeight() const;
		int getYpos() const;
		int getXpos() const;
		int getPrice() const;
		string getName() const;
		Artdisplayer getImage() const;
		string getImageName() const;
		void show() const;
		void saveToFile(ofstream & saveFile);

		friend ostream & operator<<(ostream & os, const Item & item);
};

Item::Item(ifstream & itemFile, string & line) {
	name = line;
	getline(itemFile, line);
	weight = atoi(line.c_str());
	getline(itemFile, line);
	string image = "items/" + line;
	itemImage = new Artdisplayer(image);
	getline(itemFile, line);
	price = atoi(line.c_str());
	getline(itemFile, line);
	ypos = atoi(line.c_str());
	getline(itemFile, line);
	xpos = atoi(line.c_str());
}

Item::~Item(){
	delete itemImage;
}

void Item::saveToFile(ofstream & saveFile) {
	saveFile << getName() << endl << getWeight() << endl << getImageName() << endl;
	saveFile << getPrice() << endl << getYpos() << endl << getXpos() << endl;
}

int Item::getPrice() const {
	return price;
}

int Item::getWeight() const {
	return weight;
}

string Item::getName() const {
	return name;
}
int Item::getYpos() const {
	return ypos;
}
int Item::getXpos() const {
	return xpos;
}

string Item::getImageName() const {
	return itemImage->getImageName();
}

Artdisplayer Item::getImage() const {
	return *itemImage;
}

void Item::show() const {
	cout << *itemImage;
}

ostream & operator<<(ostream & os, const Item & item) {
	size_t extraSpace = 30;
	os << item.getName() << setw(extraSpace - item.getName().length()) << item.getWeight() << endl; 
	return os;
}

#endif