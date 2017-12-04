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
	AVL<string, Player, Menor<string> > Countries;
	AVL<char, Player, Menor<char> > Positions;
	AVL<uint, Player, Menor<uint> > Ages;
	void insert(Player x){
		Players.insert(x); //inserting to the linked list
		Countries.insert(x.Country); //inserting the player's country to the Tree xdd
		Positions.insert(x.Position); //inserting the player's position to the Tree xdd
		Ages.insert(x.Age); //inserting the player's age to the Tree xdd
		CNode<string, Player >** p; //country node
		CNode<char, Player>** q; //position node
		CNode<uint, Player>** r; //ages node
		Nodo<Player>** ply; //node to the player in the linked list
		Countries.find(x.Country, p); 
		Positions.find(x.Position, q); 
		Ages.find(x.Age, r); 
		Players.find(x, ply);
		if (*p) (*p)->addPlayer(*ply); //Adding at the Countries Tree
		if (*q) (*q)->addPlayer(*ply); //Adding at the positions tree
		if (*r) (*r)->addPlayer(*ply); //Adding at the Ages tree
	}
	void remove(Player x){
		Nodo <Player> **ply;
		Players.find(x, ply);
		CNode<string, Player >** p;
		CNode<char, Player >** q;
		CNode<uint, Player>** r;
		Countries.find(x.Country, p);
		Positions.find(x.Position, q);
		Ages.find(x.Age, r); 
		if (*p) (*p)->removePlayer(*ply);
		if ( (*p) && (*p)->players.empty() ){
			Countries.remove(x.Country);
		}
		if (*q) (*q)->removePlayer(*ply);
		if ( (*q) && (*q)->players.empty() ){
			Positions.remove(x.Position);
		}
		if (*r) (*r)->removePlayer(*ply);
		if ((*r) && (*r)->players.empty() ){
			Ages.remove(x.Age);
		}
		Players.del(x);
	}
	void printByCountry(string country){
		CNode<string, Player >** p;
		Countries.find(country, p);
		if (*p) (*p)->printList();
	}
	void printByPosition(char pos){
		CNode<char, Player>** p;
		Positions.find(pos, p);
		if (*p) (*p)->printList();
	}
	void printByAgeRange(uint min, uint max){
		CNode<uint, Player>** r; //ages node
		vector< Nodo<Player>* > m_ages;
		for(min; min <= max; min++){
			if (Ages.find(min, r) ){
				for(uint i = 0; i < (*r)->players.size(); i++){
					m_ages.push_back((*r)->players.at(i) ); //llena el vector con los jugadores 
				} //de edad min
			}
		}
		sortVector<Nodo<Player>* >(m_ages); //lo ordena
		for(uint i = 0; i < m_ages.size(); i++){
			cout << m_ages.at(i)->val; //imprime ese vectorcin
		}
	}
	void FillList(){ //llena la lista con los contenidos de players.csv
		ifstream players;
		string surname, country;
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
			if (surname == "27") break; //no se porque inserta un ultimo jugador en 'blanco'
			getline(players, surname, ',');
			Temp.Age = to_uint(surname);
			getline(players, surname);
			Temp.Number = to_uint(surname);
			insert(Temp);
		}
		//Players.pop_back(); ///xd
		return;
	}
		void menu_principal()
	{
		cout << "----------------MENU PRINCIPAL----------------" << endl;
		cout << "Para insertar un jugador nuevo pulse UNO" << endl;
		cout << "Para eliminar un jugador pulse DOS" << endl;
		cout << "Para cerrar el programa pulse CERO" << endl;
		cout << "Si desea imprimir una lista de jugadores pulse TRES para elegir el criterio de insercion" << endl;
	}
	Player crear_jugador()
	{
		char posicion;
		string pais, apellido;
		uint numero, edad;
		cout << "----------------CREAR UN JUGADOR----------------" << endl;
		cout << "Siga el ejemplo:" << endl;
		cout << "Nacionalidad: Argentina" << endl;
		cout << "Apellido: Romero" << endl;
		cout << "Edad: 30" << endl;
		cout << "Numero de camiseta: 1" << endl;
		cout << "Posicion: P" << endl;
		cout << "---------------------------" << endl;
		cout << "Ingrese la nacionalidad: "; 
		getline(cin, pais);
		getline(cin, pais);
		//cin >> pais;
		while(pais[0] > 97)
		{
			cout << "ERROR" << endl;
			cout << "La primera letra tiene que ser mayuscula" << endl;
			cout << "Ingrese la nacionalidad: ";
			getline(cin, pais);
		}
		cout << "Ingrese el apellido: "; 
		getline(cin, apellido);
		cout << "Ingrese la edad: "; 
		cin >> edad;
		cout << "Ingrese el numero de camiseta: "; 
		cin >> numero;
		cout << "Ingrese la posicion siendo A atacante, M medio campista, D defensa y P portero: "; 
		cin >> posicion;
		while(posicion != 'A' && posicion != 'M' && posicion != 'D' && posicion != 'P')
		{
			cout << "ERROR" << endl;
			cout << "No se ingreso una posicion valida, preocure que sea mayuscula y una de las validas" << endl;
			cout << "Ingrese la posicion: ";
			cin >> posicion;
		}
		Player newplayer(numero, apellido, posicion, edad, pais);
		return newplayer;
	}
	Player eliminar_jugador()
	{
		char posicion;
		string pais, apellido;
		uint numero, edad;
		cout << "Siga el ejemplo:" << endl;
		cout << "Nacionalidad: Argentina" << endl;
		cout << "Apellido: Romero" << endl;
		cout << "Edad: 30" << endl;
		cout << "Numero de camiseta: 1" << endl;
		cout << "Posicion: P" << endl;
		cout << "---------------------------" << endl;
		cout << "Ingrese la nacionalidad: "; 
		getline(cin, pais);
		getline(cin, pais);
		while(pais[0] > 97)
		{
			cout << "ERROR" << endl;
			cout << "La primera letra tiene que ser mayuscula" << endl;
			cout << "Ingrese la nacionalidad: ";
			getline(cin, pais);
		}
		cout << "Ingrese el apellido: "; 
		getline(cin, apellido);
		cout << "Ingrese la edad: "; 
		cin >> edad;
		cout << "Ingrese el numero de camiseta: "; 
		cin >> numero;
		cout << "Ingrese la posicion siendo A atacante, M medio campista, D defensa y P portero: "; 
		cin >> posicion;
		while(posicion != 'A' && posicion != 'M' && posicion != 'D' && posicion != 'P')
		{
			cout << "ERROR" << endl;
			cout << "No se ingreso una posicion valida, preocure que sea mayuscula y una de las validas" << endl;
			cout << "Ingrese la posicion: ";
			cin >> posicion;
		}
		Player newplayer(numero, apellido, posicion, edad, pais);
		return newplayer;
	}
	void menu_insertar()
	{
		Nodo <Player> **ply;
		Player pl = crear_jugador();
		while(Players.find(pl, ply))
		{
			cout << "------------------------------------" << endl;
			cout << "ESE JUGADOR YA EXISTE CREE UNO NUEVO" << endl;
			cout << "------------------------------------" << endl;
			pl = crear_jugador();
		}
		insert(pl);
		cout << "------------------------------------" << endl;
		cout << "JUGADOR CORRECTAMENTE INSERTADO" << endl;
		cout << "------------------------------------" << endl;
		cout << "------------------------------------" << endl;
		int ex;
		cout << "Presione 1 para volver al MENU PRINCIPAL" << endl;
		cout << "------------------------------------" << endl;
		cin >> ex;
		while(ex != 1)
		{
			cin >> ex;
		}
	}
	void menu_eliminar()
	{
		cout << "------------------ELIMINAR JUGADOR------------------" << endl;
		Nodo <Player> **ply;
		Player pl = eliminar_jugador();
		while(!Players.find(pl, ply))
		{
			cout << "------------------------------------" << endl;
			cout << "ESE JUGADOR NO EXISTE ELIjA UNO NUEVO" << endl;
			cout << "------------------------------------" << endl;
			pl = crear_jugador();
		}
		remove(pl);
		cout << "------------------------------------" << endl;
		cout << "JUGADOR CORRECTAMENTE ELIMINADO" << endl;
		cout << "------------------------------------" << endl;
		cout << "------------------------------------" << endl;
		int ex;
		cout << "Presione 1 para volver al MENU PRINCIPAL" << endl;
		cout << "------------------------------------" << endl;
		cin >> ex;
		while(ex != 1)
		{
			cin >> ex;
		}
	}
	void cat()
	{
		cout << "----------MENU DE CRITERIOS DE LISTADO----------" << endl;
		cout << "Pulse CINCO para el Listado de los Jugadores en orden en que se ingresaron" << endl;
		cout << "Pulse SEIS para el Listado de Jugadores por seleccion" << endl;
		cout << "Pulse SIETE para el Listado de Jugadores por Posicion" << endl;
		cout << "Pulse OCHO para el Listado de Jugadores por Rangos de Edades.-" << endl;
		cout << "Pulse NUEVE para regresar al MENU PRINCIPAL" << endl;
	}
	void menu_categorias()
	{
		int m;
		cat();
		cin >> m;
		while(m != 9)
		{
			if(m == 5)
			{
				Players.print();
				cat();
				cin >> m;
				continue;
			}
			if(m == 6)
			{
				string pais;
				cout << "Ingrese un pais con la primera letra mayuscula: ";
				cin >> pais;
				while(pais[0] > 97)
				{
					cout << "ERROR" << endl;
					cout << "La primera letra tiene que ser mayuscula" << endl;
					cout << "Ingrese un pais: ";
					cin >> pais;
				}
				printByCountry(pais);
				cat();
				cin >> m;
				continue;
			}
			if(m == 7)
			{
				char posicion;
				cout << "Ingrese la posicion siendo A atacante, M medio campista, D defensa y P portero: "; 
				cin >> posicion;
				while(posicion != 'A' && posicion != 'M' && posicion != 'D' && posicion != 'P')
				{
					cout << "ERROR" << endl;
					cout << "No se ingreso una posicion valida, preocure que sea mayuscula y una de las validas" << endl;
					cout << "Ingrese la posicion: ";
					cin >> posicion;
				}
				printByPosition(posicion);
				cat();
				cin >> m;
				continue;
			}
			if(m == 8)
			{
				int min, max;
				cout << "Ingrese la edad minima: ";
				cin >> min;
				cout << "Ingrese la edad maxima: ";
				cin >> max;
				printByAgeRange(min, max);
				cat();
				cin >> m;
				continue;
			}
			else
				cin >> m;
		}
		system("cls");
		menu_principal();
	}
};


int main (int argc, char *argv[]) {
	int key;
	bool state = true;
	
	DataBase DB;
	DB.FillList();
	
	DB.menu_principal();
	while(state)
	{
		cin >> key;
		switch (key)
		{
		case 0:
			state = false;
			break;
		case 1:
			system("cls");
			DB.menu_insertar();
			system("cls");
			DB.menu_principal();
			break;
		case 2:
			system("cls");
			DB.menu_eliminar();
			system("cls");
			DB.menu_principal();
			break;
		case 3:
			system("cls");
			DB.menu_categorias();
			break;
		}
	}
	return 0;
}


/*int main (int argc, char *argv[]) {
	DataBase DB;
	Player Temp;
	Temp.Age = 15;
	Temp.Position = 'M';
	Temp.Country = "Uruguay";
	Temp.Number = 69;
	Temp.Surname = "Apellido";
	DB.insert(Temp);
	Temp.Age = 16;
	Temp.Position = 'A';
	Temp.Number = 99;
	Temp.Surname = "Apellido2";
	DB.insert(Temp);
	DB.FillList();
	DB.remove(Temp);
	//DB.Players.print();
	//DB.printByCountry("Uruguay");
	//DB.printByPosition('M');
	//DB.Ages.printTree(DB.Ages.m_root);
	DB.printByAgeRange(14, 21);
	return 0;
}*/

