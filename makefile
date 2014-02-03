CFLAGS = -g -std=c++0x -Wall

CFILES = creatures/creature.h creatures/character.h environment/environment.h backpack.h item.h main.cpp

first:
	g++ $(CFLAGS) $(CFILES) -o main.out && ./main.out

valgrind:
	g++ $(CFLAGS) $(CFILES) -o main.out && valgrind ./main.out