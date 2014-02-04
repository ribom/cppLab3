#include <iostream>
#include "creatures/character.h"
#include "environment/environment.h"

using namespace std;

class Board {
	private:
		Environment * currentMap;
		vector<Creature *> creaturesOnMap;
		vector<Environment *> usedMaps;
		string command;

	public:
		Board(const string & mapName, Creature * character);
		~Board();
		void updateMap();
		void loadCreatures(Creature * character);
		bool takeCommand();
		void tryMove(vector<string> & map, Creature * it, int & xpos, int & ypos);
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

bool Board::takeCommand() {
	cin >> command;
	if(command == "exit") {
		return false;
	}
	return true;
}

void Board::updateMap() {
	vector<string> map = currentMap->updateField();

	for(auto it = creaturesOnMap.begin(); it != creaturesOnMap.end(); ++it) {
		int xpos = (*it)->getXpos();
		int ypos = (*it)->getYpos();
		tryMove(map, *it, xpos, ypos);

		if(it == creaturesOnMap.begin()) {
			string tmp = "H";
			map[ypos][xpos] = tmp[0];
		} 
		else {
			string tmp = "M";
			map[ypos][xpos] = tmp[0];
		}
	}
	for(unsigned j = 0; j < map.size(); ++j) { 
		for (unsigned i = 0; i < map[0].size(); ++i) {
			cout << map[j][i];
		}
		cout << endl;
	}
}

void Board::tryMove(vector<string> & map, Creature * it, int & xpos, int & ypos) {
	int wantXpos = 0;
	int wantYpos = 0;
	if(command == "w") {
		wantYpos = -1;
	} else if(command == "a") {
		wantXpos = -1;
	} else if(command == "s") {
		wantYpos = 1;
	} else if(command == "d") {
		wantXpos = 1;
	}
	wantXpos += xpos;
	wantYpos += ypos;
	string tmp = "#"; 
	if(xpos < 0 || ypos < 0 || (unsigned)xpos > map[0].size() || (unsigned)ypos > map.size()) {
		cout << "lets move to the next map!!" << endl;
	}
	if(map[wantYpos][wantXpos] == tmp[0]) {
		cout << "That's the wall! And you're not a ghost, no matter what you might believe!" << endl;
	}
	else {
		it->go(wantXpos, wantYpos); 
		xpos = wantXpos;
		ypos = wantYpos;
	}
}

void Board::loadCreatures(Creature * character) {
	creaturesOnMap.push_back(character);
}