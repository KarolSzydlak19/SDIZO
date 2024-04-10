// menu.cpp : Defines the entry point for the console application.
//


#include<conio.h>
#include<string>
#include<iostream>
#include<string>
#include"Table.h"
#include"ElemList.h"
#include"Heap.h"
#include"BSTelem.h"
//#include"MeasureTable.cpp"
using namespace std;

//w³aœciwy program

void displayMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}
void displayMenuBST(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.DSW" << endl;
	cout << "8.Pomiary" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}



Table myTab; //myTab mo¿e byæ dynamiczna, mo¿e byc takze zadeklarowana w manu_table albo tutaj jako zmienna globalna 
ElemList myElemList;
ElemList* head = nullptr;
ElemList* tail = nullptr;


void menu_table()
{
	char opt;
	string fileName;
	int index, value;



	do {
		displayMenu("--- TABLICA ---");
		opt = _getch();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			myTab.loadFromFile(fileName);
			myTab.display();
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			cout << " podaj index:";
			cin >> index;
			myTab.deleteFromTable(index);
			myTab.display();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartoœæ:";
			cin >> value;

			myTab.addValue(index, value);
			myTab.display();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			cout << " podaj wartosc:";
			cin >> value;
			if (myTab.IsValueInTable(value))
				cout << "poadana wartosc jest w tablicy";
			else
				cout << "poadanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			myTab.generateTable(value);
			myTab.display();
			break;

		case '6':  //tutaj wyœwietlanie tablicy
			myTab.display();
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie bêdzie testowana przez prowadz¹cego 
			// mo¿na sobie tu dodaæ w³asne dodatkowe case'y
			//measureTable(myTab);
			myTab.measureTable();
			break;
		}

	} while (opt != '0');
}

void menu_list()
{
	//analogicznie jak menu_table()
	char opt;
	string fileName;
	int index, value;



	do {
		displayMenu("--- LISTA ---");
		opt = _getch();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  listy z pliku
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			myElemList.loadFromFile(fileName,head,tail);
			myElemList.display(head, tail);
			break;

		case '2': //tutaj usuwanie elemenu z listy
			cout << " podaj wartosc:";
			cin >> index;
			myElemList.deleteFromList(index,head,tail);
			myElemList.display(head, tail);
			break;

		case '3': //tutaj dodawanie elemetu do listy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartoœæ:";
			cin >> value;

			myElemList.addValue(index, value,head,tail);
			myElemList.display(head, tail);
			break;

		case '4': //tutaj znajdowanie elemetu w liscie
			cout << " podaj wartosc:";
			cin >> value;
			if (myElemList.IsValueInList(value,head))
				cout << "poadana wartosc jest w liscie";
			else
				cout << "poadanej wartosci NIE ma w liscie";
			break;

		case '5':  //tutaj generowanie  listy
			cout << "Podaj ilosc elementów liscie:";
			cin >> value;
			myElemList.generateList(value,head,tail);
			myElemList.display(head, tail);
			break;

		case '6':  //tutaj wyœwietlanie liscie
			myElemList.display(head, tail);
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie bêdzie testowana przez prowadz¹cego 
			myElemList.measure(head, tail);
			break;
		}

	} while (opt != '0');
}
Heap myHeap;
void menu_heap()
{
	char opt;
	string fileName;
	int index;
	int value;
	bool heap_restored;
	string  sp, sn;
	do{
		displayMenu("--- KOPIEC ---");
		opt = _getch();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  kopca z pliku
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			myHeap.loadFromFile(fileName);
			myHeap.create_heap_dn();
			heap_restored = myHeap.check_heap();
			myHeap.create_heap_dn();
			myHeap.displayHeap_t();
			myHeap.displayHeap("", "", 0);
			break;

		case '2': //tutaj usuwanie elemenu z kopca
			cout << " podaj wartosc:";
			cin >> value;
			myHeap.deleteFromHeap(value);
			//myHeap.create_heap_dn();
			myHeap.displayHeap_t();
			myHeap.displayHeap("", "", 0);
			break;

		case '3': //tutaj dodawanie elemetu do kopca
			cout << " podaj wartoœæ:";
			cin >> value;
			myHeap.addValue(value);
			//myHeap.heap_fix_down(myHeap.cnt-1);
			//heap_restored = myHeap.check_heap();
			//myHeap.create_heap_dn();
			myHeap.displayHeap_t();
			myHeap.displayHeap("", "", 0);
			break;

		case '4': //tutaj znajdowanie elemetu w kopcu
			cout << " podaj wartosc:";
			cin >> value;
			if (myHeap.isValueInHeap(value))
				cout << "poadana wartosc jest w kopcu";
			else
				cout << "poadanej wartosci NIE ma w kopcu";
			break;

		case '5':  //tutaj generowanie  kopca
			cout << "Podaj ilosc elementów kopcu"<<endl;
			cin >> value;
			myHeap.generateHeap(value);
			myHeap.create_heap_dn();
			myHeap.displayHeap_t();
			myHeap.displayHeap("", "", 0);
			break;

		case '6':  //tutaj wyœwietlanie kopca
			myHeap.displayHeap_t();
			myHeap.displayHeap("", "", 0);
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie bêdzie testowana przez prowadz¹cego 
			myHeap.heapMeasure();
			break;
		}

	} while (opt != '0');
}
BSTelem myBST;
void menu_BST() {
	char opt;
	string fileName;
	int value;
	do {
		displayMenuBST("--- BST ---");
		opt = _getch();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  listy z pliku
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			myBST.loadFromFile(fileName);
			//myBST.DSW();
			myBST.display("", "", myBST.root);
			break;

		case '2': //tutaj usuwanie elemenu z listy
			cout << " podaj wartosc:";
			cin >> value;
			myBST.deleteFromBST(myBST.root, value);
			//myBST.DSW();
			myBST.display("", "", myBST.root);

			break;

		case '3': //tutaj dodawanie elemetu do listy
			cout << " podaj wartoœæ:";
			cin >> value;
			myBST.addValue(value);
			//myBST.DSW();
			myBST.display("", "", myBST.root);

			break;

		case '4': //tutaj znajdowanie elemetu w liscie
			cout << " podaj wartosc:";
			cin >> value;
			if (myBST.IsValueInBST(value)) {
				cout << "Podana wartosc jest w BST" << endl;
			}
			else {
				cout << "Podanej wartosci nie ma w BST" << endl;
			}
			break;

		case '5':  //tutaj generowanie  listy
			cout << "Podaj ilosc elementów drzewa BST" << endl;
			cin >> value;
			myBST.generateBST(value);
			//myBST.DSW();
			myBST.display("", "", myBST.root);
			break;

		case '6':  //tutaj wyœwietlanie liscie
			myBST.display("", "", myBST.root);
			break;

		case '7': //CLT
			myBST.DSW();
			myBST.display("", "", myBST.root);
			break;

		case '8':
			myBST.measureBST();
			break;
		}

	} while (opt != '0');
}

int main(int argc, char* argv[])
{

	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Tablica" << endl;
		cout << "2.Lista" << endl;
		cout << "3.Kopiec" << endl;
		cout << "4.BST" << endl;
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
		case '4':
			menu_BST();
		}

	} while (option != '0');


	return 0;
}
