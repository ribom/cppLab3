CFLAGS = -g -std=c++0x -Wall

CFILES = creatures/creature.h creatures/character.h creatures/monster.h environment/environment.h board.h backpack.h item.h main.cpp

first:
	g++ $(CFLAGS) $(CFILES) -o main.o && ./main.o

valgrind:
	g++ $(CFLAGS) $(CFILES) -o main.o && valgrind ./main.o