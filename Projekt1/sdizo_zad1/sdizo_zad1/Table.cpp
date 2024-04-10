#include"Table.h"
#include<string>
#include<iostream>
#include<fstream>
#include<string.h>
#include<Windows.h>
#include <conio.h>
using namespace std;
Table::Table()
{
}

Table::~Table()
{
}

int Table::loadFromFile(string FileName)
{
	if (tab != nullptr) {
		delete tab;
		tab = nullptr;
	}
	cout << "Wczytywanie tabeli z pliku..." << endl;
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "Blad przy wczytywaniu pliku, nie odnaleziono pliku o zdanej nazwie"<<endl;
		return 0;
	}
	int i_fromFile = 0;
	int iteration = 0;
	int *bufor;
	int it=0;
	bufor = nullptr;
	iFile >> it;					//it okreœla iloœæ liczb w pliku
	for (int k = 0; k < it;k++) {
		if (iFile >> i_fromFile) {
			if (bufor != nullptr) {		//bufor jest tabel¹ pomocnicz¹ u¿ywan¹ przy tworzeniu nowej tablicy o wiêkszym rozmiarze
				delete bufor;
			}
			bufor = new int[iteration + 1];
			if (tab != nullptr) {
				for (int i = 0; i < iteration; i++) {	//kopiowanie zawartoœci tab do bufora
					bufor[i] = tab[i];
				}
				delete tab;
				tab = nullptr;
				tab = new int[iteration + 1];
				for (int i = 0; i < iteration; i++) {	// kopiowanie bufora do w³aœciwej tablicy
					tab[i] = bufor[i];
				}
			}
			if (tab == nullptr) {
				tab = new int[iteration + 1];
			}
			tab[iteration] = i_fromFile;				//dodanie ostatnio wczytanego elementu
			iteration++;
		}
		else {
			cout << "Nieprawidlowy format pliku, wczytano "<<k<<" wartosci" << endl;
		}
		
	}
	//tab = table;
	cnt = iteration;
	delete bufor;
	iFile.close();
	return 0;
}

bool Table::IsValueInTable(int val)
{
	for (int i = 0; i < cnt; i++) {
		if (tab[i] == val) {
			return true;
		}
	}
	return false;
}

void Table::addValue(int index, int value)
{
	if (index<0 || index>cnt + 1) {
		cout << "Nieprawidlowy index" << endl;
	}
	else {
		int* table;
		table = new int[cnt + 1];			//nowa tabela powiêkszona o rozmiar jednego elementu
		for (int i = 0; i < cnt; i++) {
			table[i] = tab[i];				//zawartoœc pierwotnej tabeli kopiowana do tej o rozmiarze cnt+1
		}
		delete tab;
		int* bufor;
		bufor = new int[cnt - index];		//bufor- nowa tabela przechowuj¹ca elementy znajduj¹ce siê na indeksach wiêkszych ni¿ tej wstawianej liczby
		int iteration = 0;
		for (int i = index; i < cnt; i++) {
			bufor[iteration] = table[i];	//wype³nienie tabeli
			iteration++;
		}
		iteration = 0;
		table[index] = value;				//wstawienie zadanej liczby				
		cnt += 1;				
		for (int i = index + 1; i < cnt; i++) {		//wstawienie do tablicy elementów o indeksie wiêskzym ni¿ indeks wstawianej liczby
			table[i] = bufor[iteration];
			iteration++;
		}
		delete bufor;
		tab = table;
	}
}

void Table::deleteFromTable(int index)
{
	if (cnt == 0)
		cout << "Tabela jest pusta!!!" << endl;
	else {
		if (index<0 || index>cnt - 1) {
			cout << "Nieprawidlowy index" << endl;

		}
		else {
			int* table;
			table = new int[cnt - 1];	//stworzenie nowej tabeli o indeksie mniejszym	
			int added = 0;
			for (int i = 0; i < cnt; i++) {	//pêtla kopiuje zawartoœæ tablicy poza tej o usuwanym indeksie
				if (i != index) {
					table[added] = tab[i];
					added++;
				}
			}
			cnt--;
			delete tab;
			tab = table;
		}
	}
}

void Table::display()
{
	cout << "Tablica: " << endl;
	cout << "[ ";
	for (int i = 0; i < cnt; i++) {
		cout << tab[i]<<" ";
	}
	cout <<"]"<<endl;
}

void Table::generateTable(int size)
{
	if (tab != nullptr) {
		delete tab;
	}
	tab = new int[size];
	int value;
	for (int i = 0; i < size; i++) {
		value = rand();
		tab[i] = value;
	}
	cnt = size;
	tab = tab;
}
// Funkcja do pomiarow czasu:
void Table::measureTable() {
		LARGE_INTEGER startTime, endTime, diffTime;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		char opt;
		int mesCount = 0;
		int size = 0;
		int min, max = 0;
		int index = 0;
		int value;
		bool result = false;
		ofstream oFile;
		do {
			cout << "Przeprowadzanie pomiarow dla tablicy" << endl;
			cout << "Wybierz opcje" << endl;
			mesDisplay();
			opt = _getch();
			if (opt == '1' || opt == '2' || opt == '3' || opt == '4' || opt == '5' || opt == '6' || opt == '7') {
				cout << "Prosze podac liczbe pomiarow: " << endl;
				mesCount = 0;
				cin >> mesCount;
				while (size < 100) {
					cout << "Prosze podac rozmiar tablicy (wiêkszy ni¿ 100): " << endl;
					cin >> size;
				}
				min, max = 0;
				cout << "Prosze podac minimalna wartosc przechowywana w tablicy" << endl;
				cin >> min;
				cout << "Prosze pdoac maksymalna wartosc przechowywana w tablicy" << endl;
				cin >> max;
				if (max < min) {
					while (max < min) {
						cout << "Wartosc maksymalna nie moze byc mniejsza od minimalnej!!!" << endl;
						cout << "Prosze podac minimalna wartosc przechowywana w tablicy" << endl;
						cin >> min;
						cout << "Prosze pdoac maksymalna wartosc przechowywana w tablicy" << endl;
						cin >> max;
					}
				}
			}
			fflush(stdin);
			switch (opt) {
			case '1':
				//dodawanie na poczatek:
				//--------zakres wartosci generowanych w tablicy 0-100
				oFile.open("tablicaPomiary/tabAdd0");
				if (oFile.is_open()) {
					oFile << "";
					oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateTable(size);
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						addValue(0, rand());
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t\t\t" << size << "\t\t\t" << min << "\t\t\t" << max << endl;
					}

				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '2':
				oFile.open("tablicaPomiary/tabAddLast");
				if (oFile.is_open()) {
					oFile << "";
					oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateTable(size);
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						addValue(cnt, rand() % max + min);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t\t\t" << size << "\t\t\t" << min << "\t\t\t" << max << endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
			case '3':
				oFile.open("tablicaPomiary/tabAddRand");
				if (oFile.is_open()) {
					oFile << "";
					oFile << "Czas operacji[ms]\tIndeksRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				cout << "dodawanie do losowego indexu" << endl;
				index = 0;
				for (int i = 0; i < mesCount; i++) {
					generateTable(size);
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						index = rand() % (cnt - 1);
						addValue(index, rand());
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t" << index << "\t\t\t" << size << "\t\t\t" << min << "\t\t\t" << max << endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
			case '4':
				oFile.open("tablicaPomiary/tabSubb0");
				if (oFile.is_open()) {
					oFile << "";
					oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateTable(size);
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 100; j++) {
							deleteFromTable(0);
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t" << index << "\t\t\t" << size << "\t\t\t" << min << "\t\t\t" << max << endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
			case '5':
				oFile.open("tablicaPomiary/tabLast");
				if (oFile.is_open()) {
					oFile << "";
					oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateTable(size);
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 100; j++) {
							deleteFromTable(cnt-1);
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t" << index << "\t\t\t" << size << "\t\t\t" << min << "\t\t\t" << max << endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
			case '6':
				oFile.open("tablicaPomiary/tabRand");
				if (oFile.is_open()) {
					oFile << "";
					oFile << "Czas operacji[ms]\tIndeks\tRozmiar tablicy\tWartosc minimalna\tWartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateTable(size);
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 100; j++) {
							index = rand() % (cnt - 1);
							deleteFromTable(index);
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t\t\t" << index << "\t\t" << size << "\t\t\t" << min << "\t\t\t" << max << endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
			case '7':
				oFile.open("tablicaPomiary/tabFind");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateTable(size);
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						value = rand() % (cnt - 1);
						result = IsValueInTable(value);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t\t\t" << size << endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
			};
		} while (opt != '0');
	
}
void Table::mesDisplay() {
	cout << "0 Wyjdz" << endl;
	cout << "1 Dodaj na poczatek" << endl;
	cout << "2 Dodaj na koniec" << endl;
	cout << "3 Dodaj z losowym indexem" << endl;
	cout << "4 Usun pierwszy indeks"<<endl;
	cout << "5 Usun ostatni indeks" << endl;
	cout << "6 Usun losowy indeks" << endl;
	cout << "7 Znajdz wartosc" << endl;
}