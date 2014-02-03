#include <iostream>
#include "creatures/character.h"
#include "environment/environment.h"

using namespace std;

class Board {
	private:
		Environment * currentMap;
		vector<Creature *> creaturesOnMap;
		vector<Environment *> usedMaps;

	public:
		Board(const string & mapName, Creature * character);
		~Board();
		void updateMap();
		void loadCreatures(Creature * character);
};

Board::Board(const string & mapName, Creature * character) {
	currentMap = new Environment(mapName);
	usedMaps.push_back(currentMap);
	loadCreatures(character);
	updateMap();
}

Board::~Board() {
	for(auto it = usedMaps.begin(); it != usedMaps.end(); ++it) {
		delete *it;
	}
}

void Board::updateMap() {
	currentMap->updateField(creaturesOnMap);
}

void Board::loadCreatures(Creature * character) {
	creaturesOnMap.push_back(character);
}