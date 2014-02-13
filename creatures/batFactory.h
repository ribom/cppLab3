#include "creatureFactory.h"
#include "bat.h"

#ifndef BAT_FACTORY
#define BAT_FACTORY

class BatFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Bat(file);}
};

#endif