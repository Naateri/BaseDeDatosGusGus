#include <iostream>
#include <vector> 
#include <string>
using namespace std;
struct Player
{
	unsigned int Number;
	string Surname;
	char Position;
	unsigned int Age;
	string Country;
	Player(){};
	Player(unsigned int number, string surname, char position, unsigned int age, string country)
	{
		Number = number;
		Surname = surname;
		Position = position;
		Age = age;
		Country = country;
	}
	bool operator==(Player A){
		if (this->Number != A.Number) return 0;
		if (this->Surname != A.Surname) return 0;
		if (this->Position != A.Position) return 0;
		if (this->Country != A.Country) return 0;
		if (this->Age != A.Age) return 0;
		return 1;
	}
};
template<class T>
class Mayor
{
public:
	inline bool operator()(T a , T b){
		return a.Number > b.Number;
	}
};
template<class T>
class Menor
{
public:
	inline bool operator()(T a , T b){
		return a.Number < b.Number;
	}
};
template<class T>
class Nodo
{
public:
	T val;
	Nodo <T> *next;
	Nodo(T val, Nodo<T> *sig)
	{
		this->val = val;
		next = sig;
	}
};
template<class T, class Comp>
class LinkedList
{
public:
	Nodo <T> *head;
	Comp cmp;
	LinkedList()
	{
		head = NULL;
	};
	LinkedList(T tam)
	{
		Nodo <T>*aux = new Nodo<T>(1, NULL);
		head = aux;
		for (int i = 3; i <= tam; i=i+2)
		{
			aux->next = new Nodo<T>(i, NULL);
			aux = aux->next;
		}
		aux->next = NULL;
	};
	void pop_back(){
		Nodo <T>**ptr = &head;
		while ( (*ptr)->next){
			ptr = &((*ptr)->next);
		}
		delete *ptr;
		*ptr = 0;
	}
	void print()
	{
		Nodo <T>*temp;
		temp = head;
		while(temp)
		{
			cout << "Apellido: " << temp->val.Surname << endl;
			cout << "Numero: " << temp->val.Number << endl;
			cout << "Posicion: " << temp->val.Position << endl;
			cout << "Edad: " << temp->val.Age << endl;
			cout << "Pais: " << temp->val.Country << endl;
			cout << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	bool find(T x, Nodo <T>**&ptr)
	{
		ptr = &head;
		/*while(*ptr != NULL && cmp((*ptr)->val, x))
		{
			ptr = &((*ptr)->next);
		}*/
		while (! *ptr){
			ptr = &((*ptr)->next);
		}
		//return *ptr && (*ptr)->val == x;
		return 0;
	}
	bool insert(T x)
	{
		Nodo <T>**ptr = &head;
		while ( *ptr != NULL ){
			ptr = &((*ptr)->next);
		}
		/*if (find(x, ptr))
		{
			return 0;
		}*/
		Nodo <T>*temp = new Nodo<T>(x, NULL);
		//temp->next = *ptr;
		(*ptr) = temp;
	}
	bool del(T x)
	{
		Nodo <T>**ptr;
		if(!find(x, ptr))
		{
			return 0;
		}
		Nodo <T>*del = *ptr;
		*ptr = (*ptr)->next;
		delete ptr;
		return 1;
	}
};
