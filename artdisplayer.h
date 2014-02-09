#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#ifndef ARTDISPLAYER_H
#define ARTDISPLAYER_H

using namespace std;

class Artdisplayer{
	private:
		string image;
		string imageName;
	public:
		Artdisplayer(const string & path);
		~Artdisplayer();
		friend ostream & operator<<(ostream & os, const Artdisplayer & artDisp);
		string getImage() const;
		string getImageName() const;
};

Artdisplayer::Artdisplayer(const string & name) { //name will contain part of the path, i.e: "items/armor"
	stringstream ss(name);
    string item;
    while (std::getline(ss, item, '/')) {
        imageName = item;
    }
    cout << "in Artdisplayer! " << endl;
	string path = "art/" + name + ".txt"; 
	ifstream imageFile;
	imageFile.open(path);
	if(imageFile.is_open() != true) {
		cout << "Could not find image with path: " << path << endl; 
		return;
	}
	string line;
	while(getline(imageFile, line)) {
		image += line + "\n";
	}
	imageFile.close();

}

Artdisplayer::~Artdisplayer(){}

string Artdisplayer::getImageName() const {
	return imageName;
}

string Artdisplayer::getImage() const {
	return image;
}

ostream & operator<<(ostream & os, const Artdisplayer & artDisp) { 
	system("clear");
	return os << artDisp.getImage() << endl;
}

#endif