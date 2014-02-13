#include "creatureFactory.h"
#include "character.h"

#ifndef CHARACTER_FACTORY
#define CHARACTER_FACTORY

class CharacterFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Character(file);}
};

#endif