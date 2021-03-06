#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
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
		string type;
		string neighbors[4];
		vector<Item *> itemVector; //just nu kan det max finnas 8 saker på varje karta
	public:
		Environment(const string & name);
		~Environment();
		void printMap() const;
		void parseMapFile(ifstream & map);
};

Environment::Environment(const string & name) : name(name) {
	ifstream map;
	parseMapFile(map);
	map.close();
}

void Environment::parseMapFile(ifstream & map) {
	string path = "environment/maps/" + name; 
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
		cout << "line: " << height << endl;
		string name = line;
		getline(map, line);
		int weigth = atoi(line.c_str());
		Item * item = new Item(weigth, name);
		getline(map, line);
		int x = atoi(line.c_str());
		getline(map, line);
		int y = atoi(line.c_str());
		environmentMap.at(x)[y] = itemCnt;
		itemVector.push_back(item);
		itemCnt++;
	}
	getline(map,description);
}

Environment::~Environment() {
	for(auto mapIterator = environmentMap.begin(); mapIterator != environmentMap.end(); ++mapIterator) {
		delete mapIterator->second;
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

#endif