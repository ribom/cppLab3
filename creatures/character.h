#include "creature.h"
#include "../backpack.h"

using namespace std;

class Character : public Creature {
	private:
		Backpack backpack;
		int position;
	
	public:
		Character(const string & name);
		~Character();

		void printBackpack() const;
};

Character::Character(const string & name) : Creature(name, "Hero", 100) {
	Item * startingArmor = new Item(5, "Leather armor");
	backpack.addItem(startingArmor);
}

Character::~Character(){};

void Character::printBackpack() const {
	cout << "Your backpack contains the following:" << endl;
	cout << backpack << endl;
}