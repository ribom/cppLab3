#include <iostream>
#include <fstream>
#include "creatures/character.h"
#include "environment/environment.h"
#include "board.h"

using namespace std;

bool readIntro();
void clearScreen();
Character startUp(bool newGame);
void createCharacter(bool newGame);
void loadMap(bool newGame);
int main() 
{
	bool run = true;
	bool newGame = readIntro();

	Character heroS = startUp(newGame);
	Character * hero = &heroS;
	createCharacter(newGame);

	loadMap(newGame);
	Board board("start.txt", hero);

	while(run) {
		run = board.takeCommand();

		clearScreen();
		board.updateMap();
		
	}
	return 0;
}

Character startUp(bool newGame) {

		cout << "The first thing you need to do is to choose a character name.\nName: ";
		string name;
		cin.ignore();
		getline(cin, name);
		Character hero(name, 10, 19);
		cout << "Great choice " << hero.getName() << "!" << endl;
		return hero;
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