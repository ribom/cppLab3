#include <iomanip>
#include <map>
#include <unordered_map>
#include "item.h"

#ifndef BACKPACK_H
#define BACKPACK_H

using namespace std;

class Backpack {
	private:
		int capacity;
		int numberOfItems;
		unordered_map<string, Item*> itemMap;
	public:
		Backpack();
		~Backpack();

		bool addItem(const Item * item);
		friend ostream & operator<<(ostream & os, const Backpack & backpack);
};

Backpack::Backpack() : capacity(100), numberOfItems(0) {}

Backpack::~Backpack() {
	for(auto mapIterator = itemMap.begin(); mapIterator != itemMap.end(); ++mapIterator) {
		delete mapIterator->second;
	}
}

bool Backpack::addItem(const Item * item) {
	auto gotItem = itemMap.find(item->getName());

	if(gotItem == itemMap.end()) {
		if(capacity - item->getWeigth() >= 0) {
			itemMap.insert(make_pair(item->getName(), const_cast<Item*>(item)));
			numberOfItems++;
			return true;
		} else {
			cout << "This item weighs to much. You need " << item->getWeigth() - capacity << " more capacity to carry it." << endl; 
		}
	}
	return false;
}

ostream & operator<<(ostream & os, const Backpack & backpack) {
	map<string, Item*> orderedItemMap(backpack.itemMap.begin(), backpack.itemMap.end());

	size_t extraSpace = 30;
	os << "Item" << setw(extraSpace - 4) << "Weigth" << endl;
	for(auto mapIterator = orderedItemMap.begin(); mapIterator != orderedItemMap.end(); ++mapIterator) { 
		os << mapIterator->second;
	}
	return os;
}

#endif