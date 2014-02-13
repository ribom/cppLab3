#include "creatureFactory.h"
#include "monster.h"

#ifndef MONSTER_FACTORY
#define MONSTER_FACTORY

class MonsterFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Monster(file);}
};

#endif