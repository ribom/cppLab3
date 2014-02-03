#include <iostream>
#include <fstream>
#include "creatures/character.h"
#include "environment/environment.h"

using namespace std;

bool readIntro();
void clearScreen();
void startUp(bool newGame);
void createCharacter(bool newGame);
void loadMap(bool newGame);
int main() 
{
	bool newGame = readIntro();

	startUp(newGame);

	createCharacter(newGame);

	loadMap(newGame);

	while(1) {
		break;
	}
	return 0;
}

void startUp(bool newGame) {
	if(newGame) {
		cout << "The first thing you need to do is to choose a character name.\nName: ";
		string name;
		cin >> name;
		Character hero(name);
		cout << "Great choice " << hero.getName() << "!" << endl;

		Environment testMap("start.txt");
		testMap.printMap();

	} else {

	}
}

void createCharacter(bool newGame) {

}

void loadMap(bool newGame) {

}

bool readIntro() {
	ifstream intro;
	intro.open("text/intro.txt");
	string line;
	while(getline(intro, line)) {
		cout << line << endl;
	}
	intro.close();
	int choice;
	cout << "Choice: ";
	cin	>> choice;
	clearScreen();
	if(choice == 1) {
		return true;
	} else {
		return false;
	}
}

void clearScreen() {
	system("clear");
}