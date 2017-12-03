#include <iostream>
#include <fstream>
#include <sstream>
#include "avl.h"

using namespace std;

typedef unsigned int uint;
typedef stringstream ss;

uint to_uint(string x){
	uint ret;
	ss convi(x);
	convi >> ret;
	return ret;
}

class DataBase{
public:
	LinkedList<Player> Players;
	void insert(Player x){
		Players.insert(x);
	}
	void remove(Player x){
		;
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
			insert(Temp);
		}
		Players.pop_back(); ///xd
		return;
	}
};


int main (int argc, char *argv[]) {
	//FillList();
	DataBase DB;
	Player Test1, Test2, Test3, Test4;
	Test1.Age = 20;
	Test1.Number = 5;
	Test1.Position = 'P';
	Test1.Surname = "Pascual";
	Test1.Country = "Peru";
	Test2.Age = 21;
	Test2.Number = 3;
	Test2.Position = 'D';
	Test2.Surname = "Melano";
	Test2.Country = "Peru";
	Test3.Age = 15;
	Test3.Number = 3;
	Test3.Position = 'A';
	Test3.Surname = "Messi Pe";
	Test3.Country = "Argentina";
	DB.insert(Test1);
	DB.insert(Test2);
	DB.insert(Test3);
	DB.Players.print();
	return 0;
}

