#include "creatureFactory.h"
#include "npc.h"

#ifndef NPC_FACTORY
#define NPC_FACTORY

class NpcFactory : public CreatureFactory {
	public:
		virtual Creature * create(ifstream & file) {return new Npc(file);}
};

#endif