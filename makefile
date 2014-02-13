CFLAGS = -g -std=c++0x -Wall

CFILES = creatures/creatureFactory.h creatures/dragon.h creatures/dragonFactory.h creatures/monsterFactory.h creatures/princessFactory.h creatures/princess.h creatures/npcFactory.h creatures/characterFactory.h creatures/creature.h creatures/character.h creatures/monster.h creatures/npc.h environment/environment.h board.h backpack.h artdisplayer.h item.h main.cpp

first:
	g++ $(CFLAGS) $(CFILES) -o main.o && ./main.o

valgrind:
	g++ $(CFLAGS) $(CFILES) -o main.o && valgrind ./main.o