#include <iostream>
#include <iomanip>
#include "artdisplayer.h"
#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item {
	private:
		int weight, xpos, ypos;
		string name;
		Artdisplayer itemImage;

	public:
		Item(const int & weigth, const string & name, const Artdisplayer & image, const int & xpos , const int & ypos);
		~Item();
		int getWeight() const;
		int getYpos() const;
		int getXpos() const;
		string getName() const;
		Artdisplayer getImage() const;
		string getImageName() const;
		void show() const;

		friend ostream & operator<<(ostream & os, const Item & item);
};

Item::Item(const int & weight, const string & name, const Artdisplayer & image, const int & xpos , const int & ypos)
 	: weight(weight), xpos(xpos), ypos(ypos), name(name), itemImage(image) {}

Item::~Item(){}

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
	return itemImage.getImageName();
}

Artdisplayer Item::getImage() const {
	return itemImage;
}

void Item::show() const {
	cout << itemImage;
}

ostream & operator<<(ostream & os, const Item & item) {
	size_t extraSpace = 30;
	os << item.getName() << setw(extraSpace - item.getName().length()) << item.getWeight() << endl; 
	return os;
}

#endif