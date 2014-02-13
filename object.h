#include "item.h"
#include "artdisplayer.h"
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
		Artdisplayer * objImage;

	public:
		Object(ifstream & object, unordered_map<int, int *> * environmentMap);
		~Object();
		bool unlock(const string & itemKey);
		const Object * getSelf() const;
		void saveToFile(ofstream & saveFile);
		string getName() const;
		string getKey() const;
		int getXpos() const;
		int getYpos() const;
		void show() const;
};

Object::Object(ifstream & object, unordered_map<int, int *> * environmentMap) {
	string line;
	getline(object, name);
	getline(object, key);
	getline(object, line);
	string image = "items/" + line;
	objImage = new Artdisplayer(image);
	getline(object, line);
	ypos = atoi(line.c_str());
	getline(object, line);
	xpos = atoi(line.c_str());

	environmentMap->at(ypos)[xpos] = -1;
}

void Object::show() const {
	cout << *objImage << endl;
}

Object::~Object() {
	delete objImage;
}

string Object::getKey() const {
	return key;
}

string Object::getName() const {
	return name;
}

int Object::getXpos() const {
	return xpos;
}

int Object::getYpos() const {
	return ypos;
}

void Object::saveToFile(ofstream & saveFile) {
	saveFile << "object" << endl << name << endl << key << endl << ypos << endl << xpos << endl;
}

const Object * Object::getSelf() const {
	return this;
}
bool Object::unlock(const string & itemKey) {
	if(itemKey == key) {
		return true;
	}
	return false;
}

#endif