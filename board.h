#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <cmath>
#include <string.h>
#include <fstream>
#include "creatures/character.h"
#include "environment/environment.h"
#include "backpack.h"
#include "creatures/creatureFactory.h"
#include "creatures/characterFactory.h"
#include "creatures/princessFactory.h"
#include "creatures/npcFactory.h"
#include "creatures/monsterFactory.h"
#include <unordered_map>

#define START_MAP "start"
#define START_PATH "environment/maps/"
#define CURRENT_MAP "CM"

using namespace std;

class Board {
	private:
		Environment * currentMap;
		unordered_map<string, Environment *> usedMaps;
		unordered_map<string, CreatureFactory *> creatureFactoryMap;
		string command;
		string info;
		vector<string> mapMatrix;

	public:
		Board();
		Board(string & name);
		~Board();
		void updateMainMap();
		void updateMaps();
		void printMapMatrix(const vector<Creature *> * creaturesOnMap);
		void loadCreature(const int & direction, Creature * character, const string & nextMap);
		bool takeCommand();
		bool tryMove(vector<string> & map, Creature * it, int & xpos, int & ypos, Environment * env);
		void enterNewMap(const int & direction, Creature * creature, Environment * environment);
		void lookForAction(vector<Creature *> * creaturesOnMap);
		bool saveGame();
		bool startNewGame();
		bool loadSavedGame(const string & name);
		void initFactoryMap();
};


Board::Board() {
	initFactoryMap();
 	startNewGame();
}

Board::Board(string & name) {
	initFactoryMap();
	bool startUp = false;
	while(!startUp) {
		system("clear");
		if(!loadSavedGame(name)) {
			string choice;
			cout << "Do you want to:\n1. Start a new game\n2. Try to load another game instance\nChoice: ";
			cin >> choice;
			if(choice == "1") {
				startUp = startNewGame();
			}
			else {
				cout << "What is the name of the instance you want to load?\nName: ";
				cin >> name;
			}
		}
		else {
			startUp = true;
		}
	}
}

Board::~Board() {
	for(auto it = usedMaps.begin(); it != usedMaps.end(); ++it) {
		delete (*it).second;
	}
	for(auto it : creatureFactoryMap) {
		delete it.second;
	}
}

void Board::initFactoryMap() {
	creatureFactoryMap.insert(make_pair("Hero", new CharacterFactory()));
	creatureFactoryMap.insert(make_pair("Monster", new MonsterFactory()));
	creatureFactoryMap.insert(make_pair("Npc", new NpcFactory()));
	creatureFactoryMap.insert(make_pair("Princess", new PrincessFactory()));
}

bool Board::loadSavedGame(const string & name) {
	string path = "savedgames/" + name + "/maps.txt"; 
	ifstream mapsFile;
	mapsFile.open(path);
	if(mapsFile.is_open() != true) {
		cout << "Could not find game instance: " << path << endl;
		return false;
	}
	string mapName;
	bool cm = false;
	while(getline(mapsFile, mapName)) {
		string filePath = "savedgames/" + name + "/" + mapName + ".txt";
		if(mapName == CURRENT_MAP) {
			cm = true;
			getline(mapsFile, mapName);
			filePath = "savedgames/" + name + "/" + mapName + ".txt";
		}
		if(usedMaps.find(mapName) == usedMaps.end()) {
			usedMaps.insert(make_pair(mapName, new Environment(mapName, filePath, creatureFactoryMap)));
		}
		if(cm) {
			cm = false;
			currentMap = usedMaps.at(mapName);
			printMapMatrix(currentMap->getCreaturesOnMap());
		}
	}
	return true;
}

bool Board::takeCommand() {
	if((*(currentMap->getCreaturesOnMap()->begin()))->action(*(currentMap->getCreaturesOnMap()->begin()))) {
		cout << "You have won!" << endl;
		return false;
	}
	cout << "\nCommand: ";
	cin >> command;
	if(command == "exit") {
		return false;
	} 
	else if(command == "save") {
		cout << "What do you want to name this instance: ";
		cin.ignore();
		return saveGame();
	}
	else if(command == "checkbp") {
		cout << "You have " << (*(currentMap->getCreaturesOnMap()->begin()))->getMoney() << " gold coins.";
		(*(currentMap->getCreaturesOnMap()->begin()))->printBackpack();
		cout << "Choose an item to handle, or type 'back' to get back to the game.\nChoice: ";
		cin >> command;
	}
	else if(command == "checkhp") {
		cout << "Your current HP is: " << (*(currentMap->getCreaturesOnMap()->begin()))->getHP() << endl;
	}
	return true;
}

bool Board::startNewGame() {
	system("clear");
	cout << "The first thing you need to do is to choose a character name.\nName: ";
	string name;
	cin.ignore();
	getline(cin, name);
	Character * hero = new Character(name);
	cout << "Great choice " << hero->getName() << "!" << endl;
	string s = "start.txt";
	string startPath = START_PATH + s;
	currentMap = new Environment(START_MAP, startPath, creatureFactoryMap);
	usedMaps.insert(make_pair(START_MAP, currentMap));
	usedMaps.at(START_MAP);
	currentMap->addCreature(hero);
	loadCreature(1, hero, START_MAP);
 	updateMaps();
 	return true;
}

bool Board::saveGame() {
	char name[100];	
	cin.getline(name, 100);

	char pathname[] = "savedgames/";
	strcat(pathname, name);
	if(mkdir(pathname, S_IRWXU) != -1) {
		ofstream mapsInUse;
		char fileName[110] = "";
		strcat(fileName, pathname);
		strcat(fileName, "/maps.txt");
		mapsInUse.open(fileName);
		for(auto it : usedMaps) {
			it.second->saveToFile(pathname);
			if(it.second == currentMap) {
				mapsInUse << CURRENT_MAP << endl;
			}
			mapsInUse << it.second->getName() << endl;
		}
		mapsInUse.close();
		cout << "Game saved in folder: " << pathname << "\nDo you want to continue playing? (y/n): ";
		cin >> command;
		if(command != "y") {
			return false;
		}
	} else {
		perror("Could not save game: ");
		if(errno == EEXIST) {
			cout << "Please choose another name: ";
			return saveGame();
		} 
		else {
			cout << "Do you want to try again? (y/n): ";
			cin >> command;
			if(command == "y") {
				return saveGame();
			}
		}
	}
	return true;
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
			string path = START_PATH + nextMap + ".txt";
			usedMaps.insert(make_pair(nextMap, new Environment(nextMap, path, creatureFactoryMap)));
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
			command = "";
			currentMap = usedMaps.at(nextMap);
			mapMatrix = currentMap->updateField();
			mapMatrix[creature->getYpos()][creature->getXpos()] = 'H';
			printMapMatrix(currentMap->getCreaturesOnMap());
			cout << endl << currentMap->getDescription() << endl;
		} 	
 	}
 	else {
 		cout << "it appears you went into oblivion..." << endl;
 	}
}

void Board::updateMaps() {
	Environment * tmpCurrent = currentMap;
	for(auto it = usedMaps.begin(); it != usedMaps.end(); ++it) {
		if(it->second == tmpCurrent) {
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
				itemOnMap = currentMap->getItem(xpos, ypos);
			}
			mapMatrix[ypos][xpos] = 'H';
		} 
		else {
			mapMatrix[ypos][xpos] = 'M';
		}
	}
	if(!enterdNewMap) {
		printMapMatrix(creaturesOnMap);
		if(itemOnMap != NULL) {
			itemOnMap->show();
			cout << "Oh! You've found an item, with the following stats: " << endl << *itemOnMap << "\nDo you want to pick it up? (y/n): ";
			cin >> command;
			if(command == "y") {
				if((*creaturesOnMap)[0]->pick_up(itemOnMap)) {
					currentMap->removeItem(xpos, ypos);
				}
			}
			printMapMatrix(creaturesOnMap);
		}
		lookForAction(creaturesOnMap);
	}
	cout << info << endl;
}

void Board::printMapMatrix(const vector<Creature *> * creaturesOnMap) {
	mapMatrix = currentMap->updateField();
	for(auto it = creaturesOnMap->rbegin(); it != creaturesOnMap->rend(); ++it) {
		int xpos = (*it)->getXpos();
		int ypos = (*it)->getYpos();
		mapMatrix[ypos][xpos] = (*it)->getMapSign();
	}
	system("clear");
	for(unsigned j = 0; j < mapMatrix.size(); ++j) { 
		for (unsigned i = 0; i < mapMatrix[0].size(); ++i) {
			cout << mapMatrix[j][i];
		}
	cout << endl;
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
	else {
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
	else if((unsigned)wantXpos > map[0].size()-1) {
		enterNewMap(3, it, env);
	}
	else if((unsigned)wantYpos > map.size()-1) {
		enterNewMap(0, it, env);
	}
	else {
		if(map[wantYpos][wantXpos] == '#') {
			if(it->getType() == "Hero") {
				info = "That's the wall! And you're not a ghost, no matter what you might believe!";
			}
		}
		else if(map[wantYpos][wantXpos] == 'O') {
			if(it->getType() == "Hero") {
				if(it->tryUnlockObject(currentMap->getObject(wantXpos, wantYpos))) {
					info = "You have unlocked the " + currentMap->getObject(wantXpos, wantYpos)->getName() + "\n";
					map[wantYpos][wantXpos] = ' ';
					currentMap->removeObject(wantXpos, wantYpos);
				}
				else {
					info = "You do not have the required item to unlock the " + currentMap->getObject(wantXpos, wantYpos)->getName() + "\n"; 
				}
			}
		}
		else {
			it->go(wantXpos, wantYpos); 
			xpos = it->getXpos();
			ypos = it->getYpos();
		}
		return false;
	}
	xpos = it->getXpos();
	ypos = it->getYpos();
	return true;
}

void Board::lookForAction(vector<Creature *> * creaturesOnMap) {
	int heroX, heroY, monsterX, monsterY, difX, difY;

	heroX = (*(creaturesOnMap->begin()))->getXpos();
	heroY = (*(creaturesOnMap->begin()))->getYpos();
	for(auto it = creaturesOnMap->begin()+1; it != creaturesOnMap->end(); ++it) {
		monsterX = (*it)->getXpos();
		monsterY = (*it)->getYpos();
		difX = abs(heroX - monsterX);
		difY = abs(heroY - monsterY);
		if(difX < 2 && difY < 2) {
			if((*it)->action(*(creaturesOnMap->begin()))) {

				if((*(creaturesOnMap->begin()))->dead()) {
					info = "The monster has defeeated you, and the game is over!";
				}
			}
			else {
				mapMatrix[monsterY][monsterX] = ' ';
				creaturesOnMap->erase(it);
				delete *it;
				--it;
			}
		}
	}
	printMapMatrix(creaturesOnMap);
}
