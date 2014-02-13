#include "creature.h"
#include <fstream>

#ifndef CREATURE_FACTORY
#define CREATURE_FACTORY

class CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) = 0;
};

#endif