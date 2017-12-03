#include <iostream>
#include <fstream>
#include <sstream>
#include "lista.h"

using namespace std;

typedef unsigned int uint;
typedef stringstream ss;

LinkedList<Player, Menor<Player> > Players;

uint to_uint(string x){
	uint ret;
	ss convi(x);
	convi >> ret;
	return ret;
}

void FillList(){
	ifstream players;
	string surname, country;
	char pos;
	uint number;
	uint age;
	Player Temp;
	players.open("players.csv");
	while( !players.eof() ){
		getline( players, country, ',' );
		Temp.Country = country;
		getline(players, surname, ',' );
		Temp.Position = surname[0];
		getline(players, surname, ',');
		Temp.Surname = surname;
		getline(players, surname, ',');
		Temp.Age = to_uint(surname);
		getline(players, surname);
		Temp.Number = to_uint(surname);
		Players.insert(Temp);
	}
	Players.pop_back(); ///xd
	return;
}

int main (int argc, char *argv[]) {
	FillList();
	Players.print();
	return 0;
}

