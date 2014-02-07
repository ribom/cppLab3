#include <iostream>
#include <fstream>
#include "creatures/character.h"
#include "environment/environment.h"
#include "board.h"
#include "artdisplayer.h"

using namespace std;

bool readIntro();
void clearScreen();
void createCharacter(bool newGame);
Board * loadSavedGame();

int main() {

	bool run = true;
	bool newGame = readIntro();
	Board * board;
	
	if(newGame) {
		board = new Board();
	}
	else {
		board = loadSavedGame();
	}


	while(run) {
		run = board->takeCommand();
		if(run) {
			clearScreen();
			board->updateMaps();
		}
	}
	delete board;
	return 0;
}

Board * loadSavedGame() {
	cout << "What is the name of the instance you want to load?\nName: ";
	string name;
	cin >> name;
	return new Board(name);
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