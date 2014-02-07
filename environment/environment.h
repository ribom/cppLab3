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
#include "../item.h"

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
		vector<Item *> itemVector; //just nu kan det max finnas 8 saker på varje karta
	public:
		Environment(const string & name, const string & path);
		~Environment();
		void printMap() const;
		string getName() const;
		void parseMapFile(ifstream & map, const string & path);
		void saveToFile(const string & pathname);
		int getHeight() const;
		int getWidth() const;
		vector<string> updateField();
		Item * getItem(const int & xpos, const int & ypos);
		void removeItem(const int & xpos, const int & ypos);
		string getNeighbor(const int direction) const;
		void addCreature(Creature * creature);
		vector<Creature *> * getCreaturesOnMap();
};

Environment::Environment(const string & name, const string & path) : name(name), path(path) {
	ifstream map;
	parseMapFile(map, path);
	map.close();
}

Environment::~Environment() {
	for(auto mapIterator = environmentMap.begin(); mapIterator != environmentMap.end(); ++mapIterator) {
		delete mapIterator->second;
	}
	for(auto it = creaturesOnMap.begin(); it != creaturesOnMap.end(); ++it) {
		delete *it;
	}
	for(auto it = itemVector.begin(); it != itemVector.end(); ++it) {
		delete *it;
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
			saveFile << it->getName() << endl << it->getWeight() << endl << it->getImageName() << endl;
			saveFile << it->getYpos() << endl << it->getXpos() << endl;
		}
	}
	saveFile << "description" << endl << description << endl;
	for(auto it : creaturesOnMap) {
		saveFile << it->getName() << endl << it->getType() << endl << it->getXpos() << endl << it->getYpos() << endl << it->getImageName() << endl;
		/*if(!(it->getBackpack().isEmpty())) {
			for(auto itemIt = it->getBackpack().getItemMap().begin(); itemIt != it->getBackpack().getItemMap().end(); ++itemIt) {
				saveFile << "item" << endl;
				saveFile << itemIt->second->getName() << endl << itemIt->second->getWeight() << endl << itemIt->second->getImageName() << endl;
				saveFile << itemIt->second->getYpos() << endl << itemIt->second->getXpos() << endl;
			}
		}*/
	}
	saveFile << "done";
	saveFile.close();
}

void Environment::parseMapFile(ifstream & map, const string & path) { 
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
		string name = line;
		getline(map, line);
		int weigth = atoi(line.c_str());
		getline(map, line);
		string image = "items/" + line;
		getline(map, line);
		int y = atoi(line.c_str());
		getline(map, line);
		int x = atoi(line.c_str());
		Item * item = new Item(weigth, name, image, x, y);
		environmentMap.at(y)[x] = itemCnt;
		itemVector.push_back(item);
		itemCnt++;
	}
	getline(map,description);
	while(getline(map, line) && line != "done") { //fetch monsters
		string cName = line;
		getline(map, line);
		string type = line;
		getline(map, line);
		int y = atoi(line.c_str());
		getline(map, line);
		int x = atoi(line.c_str());
		getline(map, line);
		string image = "creatures/" + line;
		cout << "hero skapas i: " << getName() << endl;
		if(type == "Hero") {
			
			Character * hero = new Character(cName, type, x, y, image);
			creaturesOnMap.insert(creaturesOnMap.begin(), hero);
		}
		else {
			Monster * monster = new Monster(cName, type, x, y, image);
			creaturesOnMap.push_back(monster);
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
		}
		map.push_back(row); 
	}
	return map;
}


#endif