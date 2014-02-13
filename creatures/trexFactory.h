#include "creatureFactory.h"
#include "trex.h"

#ifndef TREX_FACTORY
#define TREX_FACTORY

class TrexFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Trex(file);}
};

#endif