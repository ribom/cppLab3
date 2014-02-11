#include "item.h"
#include <iostream>
#include <unordered_map>
#include <vector>

#ifndef OBJECT_H
#define OBJECT_H

using namespace std;

class Object {
	private:
		string name;
		string key;
		int xpos, ypos;

	public:
		Object(ifstream & object, unordered_map<int, int *> * environmentMap);
		~Object();
		void unlock(const string & itemKey, unordered_map<int, int *> * environmentMap, vector<Object *> * objectVector);
		const Object * getSelf() const;
};

Object::Object(ifstream & object, unordered_map<int, int *> * environmentMap) {
	string line;
	getline(object, name);
	getline(object, key);
	getline(object, line);
	ypos = atoi(line.c_str());
	getline(object, line);
	xpos = atoi(line.c_str());

	environmentMap->at(ypos)[xpos] = -1;
}

Object::~Object() {}

const Object * Object::getSelf() const {
	return this;
}
void Object::unlock(const string & itemKey, unordered_map<int, int *> * environmentMap, vector<Object *> * objectVector) {
	if(itemKey == key) {
		environmentMap->at(ypos)[xpos] = 0;
		for(auto it = objectVector->begin(); it != objectVector->end(); ++it) {
			if((*it)->getSelf() == this) {
				objectVector->erase(it);
			}
		}
	}
}

#endif