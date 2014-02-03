#include <iostream>
#include <iomanip>
#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item {
	private:
		int weigth;
		string name;
	public:
		Item(const int & weigth, const string & name);
		int getWeigth() const;
		string getName() const;

		friend ostream & operator<<(ostream & os, const Item & item);
};

Item::Item(const int & weigth, const string & name) : weigth(weigth), name(name) {}

int Item::getWeigth() const {
	return weigth;
}

string Item::getName() const {
	return name;
}

ostream & operator<<(ostream & os, const Item & item) {
	size_t extraSpace = 30;
	os << item.getName() << setw(extraSpace - item.getName().length()) << item.getWeigth() << endl; 
	return os;
}

#endif