#include "creatureFactory.h"
#include "princess.h"

#ifndef PRINCESS_FACTORY
#define PRINCESS_FACTORY

class PrincessFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Princess(file);}
};

#endif