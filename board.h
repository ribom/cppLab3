#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include "creatures/character.h"
#include "environment/environment.h"
#include <unordered_map>

using namespace std;

class Board {
	private:
		Environment * currentMap;
		unordered_map<string, Environment *> usedMaps;
		string command;
		string info;
		vector<string> mapMatrix;

	public:
		Board(const string & mapName, Creature * character);
		~Board();
		void updateMainMap();
		void updateMaps();
		void printMapMatrix();
		void loadCreature(const int & direction, Creature * character, const string & nextMap);
		bool takeCommand();
		bool tryMove(vector<string> & map, Creature * it, int & xpos, int & ypos, Environment * env);
		void enterNewMap(const int & direction, Creature * creature, Environment * environment);
};


Board::Board(const string & mapName, Creature * character) {
	currentMap = new Environment(mapName);
	usedMaps.insert(make_pair(mapName, currentMap));
	usedMaps.at(mapName);
	currentMap->addCreature(character);
	loadCreature(1, character, mapName);
 	updateMaps();
 	
}

Board::~Board() {
	for(auto it = usedMaps.begin(); it != usedMaps.end(); ++it) {
		delete (*it).second;
	}
}

void Board::loadCreature(const int & direction, Creature * character, const string & nextMap) {
	if(direction == 0) {
		character->go(usedMaps.at(nextMap)->getWidth() / 2, 0);
	}
	else if(direction == 1) {
		character->go(usedMaps.at(nextMap)->getWidth() / 2, usedMaps.at(nextMap)->getHeight()-1);
	}
	else if(direction == 2) {
		character->go(usedMaps.at(nextMap)->getWidth()-1, usedMaps.at(nextMap)->getHeight() / 2);
	}
	else if(direction == 3) {
		character->go(0, usedMaps.at(nextMap)->getHeight() / 2); 
	}
	
}

void Board::enterNewMap(const int & direction, Creature * creature, Environment * environment) {
	string nextMap = environment->getNeighbor(direction);
	if(nextMap != "0") {
		if(usedMaps.find(nextMap) == usedMaps.end()) {
			usedMaps.insert(make_pair(nextMap, new Environment(nextMap)));
		}
		vector<Creature *> * creaturesOnMap = environment->getCreaturesOnMap();
		for(auto it = creaturesOnMap->begin(); it != creaturesOnMap->end(); ++it) {
			if(*it == creature) {
				creaturesOnMap->erase(it);
				break;
			}
		}
		usedMaps.at(nextMap)->addCreature(creature);
		loadCreature(direction, creature, nextMap);
		if(creature->getType() == "Hero") {
			currentMap = usedMaps.at(nextMap);
		}
	 	
 	}
 	else {
 		cout << "it appears you went into oblivion..." << endl;
 	}
}

bool Board::takeCommand() {
	cout << "\nCommand: ";
	cin >> command;
	if(command == "exit") {
		return false;
	}
	return true;
}

void Board::updateMainMap() {
	info = "";
	bool enterdNewMap;
	vector<Creature *> * creaturesOnMap = currentMap->getCreaturesOnMap();
	mapMatrix = currentMap->updateField();
	Item * itemOnMap = NULL;
	int xpos, ypos;
	for(auto it = creaturesOnMap->rbegin(); it != creaturesOnMap->rend(); ++it) {
		xpos = (*it)->getXpos();
		ypos = (*it)->getYpos();
		enterdNewMap = tryMove(mapMatrix, *it, xpos, ypos, currentMap);

		if((*it)->getType() == "Hero") {
			if(mapMatrix[ypos][xpos] == 'I') {
				itemOnMap = currentMap->getItem(ypos, xpos);
			}
			mapMatrix[ypos][xpos] = 'H';
		} 
		else {
			mapMatrix[ypos][xpos] = 'M';
		}
	}
	if(!enterdNewMap) {
		printMapMatrix();
		if(itemOnMap != NULL) {
			cout << "Oh! You've found an item, with the following stats: " << endl << *itemOnMap << "\nDo you want to pick it up? (y/n): ";
			cin >> command;
			if(command == "y") {
				if((*creaturesOnMap)[0]->pick_up(itemOnMap)) {
					currentMap->removeItem(xpos, ypos);
				}
			}
		}
	}
	cout << info << endl;
}

void Board::printMapMatrix() {
	for(unsigned j = 0; j < mapMatrix.size(); ++j) { 
		for (unsigned i = 0; i < mapMatrix[0].size(); ++i) {
			cout << mapMatrix[j][i];
		}
	cout << endl;
	}
}

void Board::updateMaps() {
	for(auto it = usedMaps.begin(); it != usedMaps.end(); ++it) {
		if(it->second == currentMap) {
			updateMainMap();
		} 
		else {
			vector<Creature *> * creaturesOnMap = it->second->getCreaturesOnMap();
			vector<string> map = it->second->updateField();
			for(auto itCreature = creaturesOnMap->rbegin(); itCreature != creaturesOnMap->rend(); ++itCreature) {
				int xpos = (*itCreature)->getXpos();
				int ypos = (*itCreature)->getYpos();
				tryMove(map, *itCreature, xpos, ypos, it->second);
			}
		}
	}
}

bool Board::tryMove(vector<string> & map, Creature * it, int & xpos, int & ypos, Environment * env) {
	int wantXpos = 0;
	int wantYpos = 0;
	if(it->getType() == "Hero") {
		if(command == "w") {
			wantYpos = -1;
		} else if(command == "a") {
			wantXpos = -1;
		} else if(command == "s") {
			wantYpos = 1;
		} else if(command == "d") {
			wantXpos = 1;
		}
	}
	else if(it->getType() == "Monster") {
		srand (time(NULL));
		wantXpos = (rand() % 3 + 1)-2;
		wantYpos = (rand() % 3 + 1)-2;
	}
	wantXpos += xpos;
	wantYpos += ypos;
	if(wantXpos < 0) {
		enterNewMap(2, it, env);
	}
	else if(wantYpos < 0) {
		enterNewMap(1, it, env);
	}
	else if((unsigned)wantXpos > map.size()-1) {
		enterNewMap(3, it, env);
	}
	else if((unsigned)wantYpos > map[0].size()-1) {
		enterNewMap(0, it, env);
	}
	else {
		if(map[wantYpos][wantXpos] == '#') {
			if(it->getType() == "Hero") {
				info = "That's the wall! And you're not a ghost, no matter what you might believe!";
			}
		}
		else {
			it->go(wantXpos, wantYpos); 
			xpos = wantXpos;
			ypos = wantYpos;
		}
		return false;
	}
	return true;
}
