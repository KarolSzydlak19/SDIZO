// menu.cpp : Defines the entry point for the console application.
//


#include<conio.h>
#include<string>
#include<iostream>
#include"Amatrix.h"
#include"List.h"
using namespace std;






//w³aœciwy program

void displayMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Algorytm Djikstry" << endl;
	cout << "3.Generuj graf " << endl;
	cout << "4.Wyswietl" << endl;
	cout << "5.Pomiary" << endl;
	//cout << "6.Wyswietl" << endl;
	//cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void displayMenuMST(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Algorytm Prima" << endl;
	cout << "3.Algorytm Kruskala" << endl;
	cout << "4.Generuj graf do MST" << endl;
	cout << "5.Wyswietl" << endl;
	cout << "6.Pomiary" << endl;
	//cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}


Amatrix matrix;
List Al;

void menu_table()
{
	char opt;
	string fileName;
	int index, value;



	do {
		displayMenu("--- Short Path ---");
		opt = _getch();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			matrix.loadFromFileMST(fileName);
			matrix.printMatrix();
			Al.loadFromFileMST(fileName);
			Al.printList();
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			matrix.Djikstra();
			Al.Djikstra();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			int V, P;
			cout << "Prosze podac liczbe wierzcholkow:" << endl;
			cin >> V;
			cout << "Prosze podac gestosc grafu (liczba calkowita" << endl;
			cin >> P;
			matrix.generateDirected(V,P);
			Al.generateDirected(matrix.matrix, V);
			matrix.printMatrix();
			Al.printList();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			matrix.printMatrix();
			Al.printList();
			break;

		case '5':  //tutaj generowanie  tablicy
			Al.SPmeasure(matrix);
			matrix.SPmeasure();
			Al.SPmeasure(matrix);
			break;

		case '6':  //tutaj wyœwietlanie tablicy
			
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie bêdzie testowana przez prowadz¹cego 
			// mo¿na sobie tu dodaæ w³asne dodatkowe case'y
			break;
		}

	} while (opt != '0');
}

void menu_list()
{
	char opt;
	string fileName;
	int index, value;
	int nodes = 0;
	


	do {
		displayMenuMST("--- MST ---");
		opt = _getch();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			matrix.loadFromFileForMST(fileName);
			matrix.printMatrix();
			Al.loadFromFileForMST(fileName);
			Al.printList();
			//Al.loadFromFileMST(fileName, head);
			//Al.printList(head);
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			matrix.PrimAlgorithm();
			Al.PrimAlgorithm();
			break;

		case '3': 
			matrix.Kruskal();
			Al.Kruskal();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			int V, P;
			cout << "Prosze podac liczbe wierzcholkow:" << endl;
			cin >> V;
			cout << "Prosze podac gestosc grafu (liczba calkowita" << endl;
			cin >> P;
			nodes = matrix.generateUndirected(V, P);
			matrix.printMatrix();
			Al.generateUndirected(matrix.matrix, nodes);
			Al.printList();
			break;

		case '5':  //tutaj generowanie  tablicy
			matrix.printMatrix();
			Al.printList();

			break;

		case '6':  //tutaj wyœwietlanie tablicy
			Al.MSTmeasure(matrix);
			matrix.MSTmeasure();
			Al.MSTmeasure(matrix);
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie bêdzie testowana przez prowadz¹cego 
			// mo¿na sobie tu dodaæ w³asne dodatkowe case'y
			break;
		}

	} while (opt != '0');
}

void menu_heap()
{
	
}

int main(int argc, char* argv[])
{

	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Algorytm najkrotszej drogi" << endl;
		cout << "2.MST" << endl;
		//cout << "3.Kopiec" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getch();
		cout << endl;

		switch (option) {
		case '1':
			menu_table();
			break;

		case '2':
			menu_list();
			break;

		case '3':
			menu_heap();
			break;
		}

	} while (option != '0');


	return 0;
}
