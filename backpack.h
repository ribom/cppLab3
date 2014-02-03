#include <iomanip>
#include <map>
#include <unordered_map>
#include "item.h"

using namespace std;

class Backpack {
	private:
		int capacity;
		int numberOfItems;
		unordered_map<string, Item*> itemMap;
	public:
		Backpack();
		~Backpack();

		void addItem(const Item * item);
		friend ostream & operator<<(ostream & os, const Backpack & backpack);
};

Backpack::Backpack() : capacity(100), numberOfItems(0) {}

Backpack::~Backpack() {
	for(auto mapIterator = itemMap.begin(); mapIterator != itemMap.end(); ++mapIterator) {
		delete mapIterator->second;
	}
}

void Backpack::addItem(const Item * item) {
	auto gotItem = itemMap.find(item->getName());

	if(gotItem == itemMap.end()) {
		if(capacity - item->getWeigth() >= 0) {
			itemMap.insert(make_pair(item->getName(), const_cast<Item*>(item)));
			numberOfItems++;
		} else {
			cout << "This item weighs to much. You need " << item->getWeigth() - capacity << " more capacity to carry it." << endl; 
		}
	}
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