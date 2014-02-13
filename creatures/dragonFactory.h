#include "creatureFactory.h"
#include "dragon.h"

#ifndef DRAGON_FACTORY
#define DRAGON_FACTORY

class DragonFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Dragon(file);}
};

#endif