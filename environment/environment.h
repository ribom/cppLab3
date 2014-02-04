#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include "../creatures/creature.h"
#include "../creatures/monster.h"
#include "../item.h"

#define NUMBER_OF_ITEM_ATTRIBUTES 4

using namespace std;

class Environment {
	private:
		string name;
		int width;
		int height;
		string description;
		unordered_map<int, int *> environmentMap;
		vector<Creature *> creaturesOnMap;
		string type;
		string neighbors[4]; // 0 = south, 1 = north, 2 = west, 3 = east
		vector<Item *> itemVector; //just nu kan det max finnas 8 saker på varje karta
	public:
		Environment(const string & name);
		~Environment();
		void printMap() const;
		void parseMapFile(ifstream & map);
		int getHeight() const;
		int getWidth() const;
		vector<string> updateField();
		Item * getItem(int xpos, int ypos);
		void removeItem(int xpos, int ypos);
		string getNeighbor(const int direction) const;
		void addCreature(Creature * creature);
		vector<Creature *> * getCreaturesOnMap();
};

Environment::Environment(const string & name) : name(name) {
	ifstream map;
	parseMapFile(map);
	map.close();
}

void Environment::addCreature(Creature * creature) {
	if(creature->getType() == "Hero") {
		creaturesOnMap.insert(creaturesOnMap.begin(), creature);
	}
	else {
		creaturesOnMap.push_back(creature);
	}
}
vector<Creature *> * Environment::getCreaturesOnMap() {
	return &creaturesOnMap;
}

string Environment::getNeighbor(const int direction) const {
	return neighbors[direction];
}

Item * Environment::getItem(int ypos, int xpos) {
	return itemVector.at(environmentMap.at(ypos)[xpos]-2);
}

void Environment::removeItem(int xpos, int ypos) {
	itemVector.at(environmentMap.at(ypos)[xpos]-2) = NULL;
	environmentMap.at(ypos)[xpos] = 0;
}

void Environment::parseMapFile(ifstream & map) {
	string path = "environment/maps/" + name + ".txt"; 
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
	width = line.length();

	for(int j = 0; j < height; ++j) {
		getline(map, line);
		int * side = new int[width];
		for(int i = 0; i < width; ++i) {
			side[i] = line[i] - 48;
		}
		environmentMap.insert(make_pair(j, side));
	}
	int itemCnt = 2;
	while(getline(map, line) && line != "description") {
		// cout << "line: " << height << endl;
		string name = line;
		getline(map, line);
		int weigth = atoi(line.c_str());
		Item * item = new Item(weigth, name);
		getline(map, line);
		int y = atoi(line.c_str());
		getline(map, line);
		int x = atoi(line.c_str());
		environmentMap.at(y)[x] = itemCnt;
		itemVector.push_back(item);
		itemCnt++;
	}
	getline(map,description);
	while(getline(map, line) && line != "done") { //fetch monsters
		string name = line;
		getline(map, line);
		int y = atoi(line.c_str());
		getline(map, line);
		int x = atoi(line.c_str());
		Monster * monster = new Monster(name, x, y);
		creaturesOnMap.push_back(monster);
	}
}

Environment::~Environment() {
	for(auto mapIterator = environmentMap.begin(); mapIterator != environmentMap.end(); ++mapIterator) {
		environmentMap.erase(mapIterator->first);
		delete mapIterator->second;
	}
	for(auto it = creaturesOnMap.begin(); it != creaturesOnMap.end(); ++it) {
		creaturesOnMap.erase(it);
		delete *it;
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
		}
		map.push_back(row); 
	}
	return map;
}


#endif