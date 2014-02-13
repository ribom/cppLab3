#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include "../creatures/creature.h"
#include "../creatures/monster.h"
#include "../creatures/character.h"
#include "../creatures/creatureFactory.h"
#include "../creatures/npc.h"
#include "../backpack.h"
#include "../item.h"
#include "../object.h"

#define NUMBER_OF_ITEM_ATTRIBUTES 4
#define ITEM_START_CNT 2

using namespace std;

class Environment {
	private:
		string name, path;
		int width;
		int height;
		string description;
		unordered_map<int, int *> environmentMap;
		vector<Creature *> creaturesOnMap;
		string type;
		string neighbors[4]; // 0 = south, 1 = north, 2 = west, 3 = east
		vector<Item *> itemVector;
		vector<Object *> objectVector;
	public:
		Environment(const string & name, const string & path, const unordered_map<string, CreatureFactory *> & creatureFactoryMap);
		~Environment();
		void printMap() const;
		string getName() const;
		void parseMapFile(ifstream & map, const string & path, const unordered_map<string, CreatureFactory *> & creatureFactoryMap);
		void saveToFile(const string & pathname);
		int getHeight() const;
		int getWidth() const;
		string getDescription() const;
		vector<string> updateField();
		Item * getItem(const int & xpos, const int & ypos);
		Object * getObject(const int & xpos, const int & ypos);
		void removeObject(const int & xpos, const int & ypos);
		void removeItem(const int & xpos, const int & ypos);
		string getNeighbor(const int direction) const;
		void addCreature(Creature * creature);
		Item * parseItem(ifstream & map, string & line);
		vector<Creature *> * getCreaturesOnMap();
};

Environment::Environment(const string & name, const string & path, const unordered_map<string, CreatureFactory *> & creatureFactoryMap) 
	: name(name), path(path) {
		ifstream map;
		parseMapFile(map, path, creatureFactoryMap);
		map.close();
}

Environment::~Environment() {
	for(auto mapIterator = environmentMap.begin(); mapIterator != environmentMap.end(); ++mapIterator) {
		delete[] mapIterator->second;
	}
	for(auto it = creaturesOnMap.begin(); it != creaturesOnMap.end(); ++it) {
		delete *it;
	}
	for(auto it = itemVector.begin(); it != itemVector.end(); ++it) {
		delete *it;
	}
	for(auto it : objectVector) {
		delete it;
	}
}

void Environment::addCreature(Creature * creature) {
	if(creature->getType() == "Hero") {
		creaturesOnMap.insert(creaturesOnMap.begin(), creature);
	}
	else {
		creaturesOnMap.push_back(creature);
	}
}

string Environment::getDescription() const {
	return description;
}

string Environment::getName() const {
	return name;
}

vector<Creature *> * Environment::getCreaturesOnMap() {
	return &creaturesOnMap;
}

string Environment::getNeighbor(const int direction) const {
	return neighbors[direction];
}

Item * Environment::getItem(const int & xpos, const int & ypos) {
	return itemVector.at(environmentMap.at(ypos)[xpos]-2);
}

Object * Environment::getObject(const int & xpos, const int & ypos) {
	Object * ret;
	for(auto it : objectVector) {
		if(it->getXpos() == xpos && it->getYpos() == ypos) {
			ret = it;
		}
	}
	return ret;
}

void Environment::removeObject(const int & xpos, const int & ypos) {
	environmentMap.at(ypos)[xpos] = 0;	
}

void Environment::removeItem(const int & xpos, const int & ypos) {
	itemVector.at(environmentMap.at(ypos)[xpos]-2) = NULL;
	environmentMap.at(ypos)[xpos] = 0;
}

void Environment::saveToFile(const string & pathname) {
	ofstream saveFile;
	string fileName = pathname + "/" + name + ".txt";
	saveFile.open(fileName);
	saveFile << name << endl;
	for(auto it : neighbors) {
		saveFile << it << endl;
	}
	saveFile << height << endl << width  << endl;
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			saveFile << environmentMap.at(y)[x];
		}
		saveFile << endl;
	}
	for(auto it : itemVector) {
		if(it != NULL) {
			it->saveToFile(saveFile);
		}
	}
	saveFile << "description" << endl << description << endl;
	for(auto it : objectVector) {
		it->saveToFile(saveFile);
	}
	for(auto it : creaturesOnMap) {
		it->saveToFile(saveFile);
		if(!(it->getBackpack()->isEmpty())) {
			for(auto itemIt = it->getBackpack()->getItemMap()->begin(); itemIt != it->getBackpack()->getItemMap()->end(); ++itemIt) {
				saveFile << "item" << endl;
				itemIt->second->saveToFile(saveFile);
			}
		}
	}
	saveFile << "done";
	saveFile.close();
}

void Environment::parseMapFile(ifstream & map, const string & path, const unordered_map<string, CreatureFactory *> & creatureFactoryMap) { 
	map.open(path);
	if(map.is_open() != true) {
		cout << "Could not find map: " << path << endl; 
		return;
	}
	string line;
	getline(map, type);
	for(int i = 0; i < 4; ++i) getline(map, neighbors[i]);
	getline(map, line);
	height = atoi(line.c_str());
	getline(map, line);
	width = atoi(line.c_str());

	for(int j = 0; j < height; ++j) {
		getline(map, line);
		int * side = new int[width];
		for(int i = 0; i < width; ++i) {
			side[i] = line[i] - 48;
		}
		environmentMap.insert(make_pair(j, side));
	}
	int itemCnt = ITEM_START_CNT;
	while(getline(map, line) && line != "description") {
		Item * item = new Item(map, line);
		environmentMap.at(item->getYpos())[item->getXpos()] = itemCnt;
		itemVector.push_back(item);
		itemCnt++;
	}
	getline(map, description);
	while(getline(map, line) && line == "object") {
		objectVector.push_back(new Object(map, &environmentMap));
	}

	while(getline(map, line)) { //fetch creatures
		if(creatureFactoryMap.find(line) != creatureFactoryMap.end()) {
			creaturesOnMap.push_back(creatureFactoryMap.at(line)->create(map));
		}
	}
}

void Environment::printMap() const {
	map<int, int *> orderedItemMap(environmentMap.begin(), environmentMap.end());

	for(auto mapIterator = orderedItemMap.begin(); mapIterator != orderedItemMap.end(); ++mapIterator) { 
		for (int i = 0; i < width; ++i) {
			cout << (mapIterator->second)[i] << " ";
		}
		cout << endl;
	}

	cout << "Items on map: " << endl;
	for(auto it = itemVector.begin(); it != itemVector.end(); ++it) {
		cout << **it;
	}

	cout << "Description:\n" << description << endl;
}

int Environment::getHeight() const {
	return height;
}

int Environment::getWidth() const {
	return width;
}

vector<string> Environment::updateField() {
	map<int, int *> orderedItemMap(environmentMap.begin(), environmentMap.end());
	vector<string> map;
	for(auto mapIterator = orderedItemMap.begin(); mapIterator != orderedItemMap.end(); ++mapIterator) {
		string row;
		for (int i = 0; i < width; ++i) {
			if(mapIterator->second[i] == 0) {
				row += " ";
			}
			else if(mapIterator->second[i] == 1) {
				row += "#";
			}
			else if(mapIterator->second[i] > 1) {
				row += "I";
			}
			else if(mapIterator->second[i] == -1) {
				row += "O";
			}
		}
		map.push_back(row); 
	}
	return map;
}


#endif