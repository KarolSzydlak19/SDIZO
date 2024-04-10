#include<iostream>
#include <string>
#include"ElemList.h"
#include<fstream>
#include <conio.h>
#include<Windows.h>
using namespace std;


	ElemList::ElemList() {

	}
	//konstruktor-wywo³ywany automatycznie przy tworzeniu obieku
	ElemList::~ElemList() {
	
	} //destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	int ElemList::loadFromFile(string FileName, ElemList *&head,ElemList *&tail) {
		ElemList* buf = head;
		while (head != nullptr) {		//usuniecie istniejacej listy
			buf = buf->next;
			delete head;
			head = buf;
		}
		tail = nullptr;
		cout << "Wczytywanie listy z pliku..." << endl;
		ifstream iFile;
		iFile.open(FileName);
		if (!iFile.is_open()) {
			cout << "Blad przy wczytywaniu pliku, nie odnaleziono pliku o zdanej nazwie" << endl;
			return 0;
		}
		cout << "Otwarto plik " << endl;
		int i_fromFile=0;
		int size;
		int datRead;
		iFile >> size;				//size okreœla iloœæ elementów w liœcie 
		int iteration = 0;
		int number=0;
		for (int k = 0; k < size;k++) {
			if (iFile >> i_fromFile) {
				ElemList* elem = new ElemList;
				elem->data = i_fromFile;	//wczytanie danych do elementu listy
				elem->next = nullptr;
				if (head == nullptr) {		//jeœli warunek jest prawdziwy lista jest pusta, wiêc dodany element staje siê g³ow¹ i ogonem
					head = elem;
					tail = elem;
				}
				else {
					tail->next = elem;		// w przeciwnym wypadku ogon zaczyna wskazywaæ na nowy element, który staje siê ogonem
					tail->next->prev = tail;
					tail = elem;
				}
				iteration++;
				number++;
			}
			else {
				cout << "Nieprawidlowy format pliku, wczytano " << number << " wartosci" << endl;
			}
	
		}
		iFile.close();
		return 0;
	}

	bool ElemList::IsValueInList(int val, ElemList *head) {
		ElemList* elem = head;
		while (elem != nullptr) {
			if (elem->data == val){ //dopóki nie dotarto do ogona sprawdzana jest zawartoœæ kolejnych elementów w liœcie, jeœli warunek jest spe³niony zwracana jest wartoœæ true
				return true;
				}
			elem = elem->next;
		}
		return false;
	}

	void ElemList::addValue(int index, int value, ElemList *&head,ElemList *&tail) {
		if (index < 0) {
			cout << "Nieprawidlowy indeks!!!" << endl;
			return;
		}
		ElemList* elem = new ElemList;
		elem->data = value;
		ElemList* currElem = head;
		if (head == nullptr) {
			head = elem;
			tail = elem;
			return;
		}
		if (index == 0) {			//jeœli indeksem jest 0 nowy element staje siê g³ow¹
			elem->next = head;
			head->prev = elem;
			head = elem;
			return;
		}
		for (int i = 0; i < index-1; i++) {
			if (currElem->next == nullptr) {
				cout << "Podany indeks wykracza poza aktualny rozmiar listy, element zostanie dodany na koniec" << endl;
				tail->next = elem;
				elem->prev = tail;
				tail = elem;
				return;
			}
			currElem = currElem->next;
		}
		elem->next = currElem->next;	//nowy element zaczyna wskazywaæ na nastêpny
		elem->prev = currElem;
		if (elem->next == nullptr) {
			tail = elem;
		}
		if (currElem->next != nullptr) {
			currElem->next->prev = elem;

		}
		currElem->next = elem;			//element o indeksie index-1 wskazywaæ zaczyna na nowy element
	}

	void ElemList::deleteFromList(int val, ElemList*& head, ElemList*& tail) {
		if (head == nullptr) {
			cout << "Lista jest pusta!!" << endl;
			return;
		}
		if (tail->data == val) {
			ElemList* currtail = tail->prev;
			delete tail;
			tail = currtail;
			return;
		}
		ElemList* elem = head;
		ElemList* currElem = head;
		while (elem->data != val) {
			if (elem->next == nullptr) {
				//cout << "W liscie nie ma podanej wartosci!!" << endl;
				return;
			}
			elem = elem->next;
		}
		if (elem == head) {				// usuwanie glowy
			if (elem->next != nullptr) {
				elem = elem->next;
				delete head;
				elem->prev = nullptr;
				head = elem;
			}
			else {						//w liscie byl 1 element
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			return;
		}
		if (elem == tail) {				//ususwanie ogona
			if (elem->prev != nullptr) {
				elem = elem->prev;
				delete tail;
				elem->next = nullptr;
				tail = elem;
			}
			else {						//w liscie byl 1 element
				delete tail;
				head = nullptr;
				tail = nullptr;
			}
			return;
		}
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		delete elem;
		return;

	}

	void ElemList::display(ElemList *head, ElemList *tail) {
		ElemList* elem = head;
		cout << "[ ";
		while (elem != nullptr) {
			cout << elem->data << " ";
			elem = elem->next;
		}
		cout <<" ]"<< endl;
		elem = tail;
		cout << "[ ";
		while (elem != nullptr) {
			cout << elem->data << " ";
			elem = elem->prev;
		}
		cout << " ]" << endl;
	}

	void ElemList::generateList(int size, ElemList *&head,ElemList *&tail) { //funkcja dodaje losowo generowane elementy do listy
		ElemList* buf = head;
		while (head != nullptr) {
			buf = buf->next;
			delete head;
			head = buf;
		}
		tail = nullptr;
		int value = 0;
		for (int i = 0; i < size; i++) {
			value = rand();
			ElemList* elem = new ElemList;
			elem->data = value;
			elem->next = nullptr;
			if (head == nullptr) {
				head = elem;
				tail = elem;
			}
			else {
				tail->next = elem;
				tail->next->prev = tail;
				tail = elem;
			}
		}
	};
	void ElemList::measure(ElemList *&head,ElemList *&tail) {
		LARGE_INTEGER startTime, endTime, diffTime;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		char opt;
		int mesCount = 0;
		int size = 0;
		int min, max = 0;
		min = 0;
		int index = 0;
		int value;
		bool result = false;
		ofstream oFile;
		do {
			cout << "Przeprowadzanie pomiarow dla listy" << endl;
			cout << "Wybierz opcje" << endl;
			mesDisplay();
			opt = _getch();
			if (opt == '1' || opt == '2' || opt == '3' || opt == '4' || opt == '5' || opt == '6' || opt == '7') {
				/*cout << "Prosze podac liczbe pomiarow: " << endl;
				mesCount = 0;
				cin >> mesCount;
				cout << "Prosze podac wartosc minimalna przechowywana w liscie" << endl;
				cin >> min;
				cout << "Prosze podac wartosc maksymalna przechowywana w liscie" << endl;
				cin >> max;*/
				mesCount = 100;
				cout << "Rozmiar?" << endl;
				cin >> size;

			}
			fflush(stdin);
			switch (opt) {
			case '1':
				//dodawanie na poczatek:
				//--------zakres wartosci generowanych w tablicy 0-100
				oFile.open("listaPomiary/listAdd0");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateListInRange(size,head,tail,min,max);
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						addValue(0, rand(),head,tail);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t\t\t" << size << endl;
					}

				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '2':
				oFile.open("listaPomiary/ListAddLast");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateListInRange(size, head, tail, min, max);
					int lcnt = 0;
					ElemList *mes = head;
					while (mes->next != nullptr) {
						mes = mes->next;
						lcnt++;
					}
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						addTail(rand(), tail);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t\t\t" << size <<  endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '3':
				oFile.open("listaPomiary/listAddRand");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tIndeksRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				cout << "dodawanie do losowego indexu" << endl;
				index = 0;
				for (int i = 0; i < mesCount; i++) {
					generateListInRange(size, head, tail, min, max);
					ElemList* mes = head;
					int lcnt = 0;
					while (mes->next != nullptr) {
						mes = mes->next;
						lcnt++;
					}
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						index = rand() % (size - 1);
						addValue(index, rand(), head,tail);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << "\t" << size << endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '4':
				oFile.open("listaPomiary/ListSubb0");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateListInRange(size, head, tail, min, max);
						int toDel = head->data;
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 100; j++) {
							deleteHead(head,tail);
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t" << size << endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '5':
				oFile.open("listaPomiary/ListSubLast");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateListInRange(size, head, tail, min, max);
						ElemList* mes = head;
						int lcnt = 0;
						while (mes->next != nullptr) {
							mes = mes->next;
							lcnt++;
						}
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 100; j++) {
							deleteTail(head, tail);
							//lcnt--;
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t" << size << endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '6':
				oFile.open("listaPomiary/listRand");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tIndeks\tRozmiar tablicy\tWartosc minimalna\tWartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateListInRange(size, head, tail, min, max);
						ElemList* mes = head;
						int lcnt = 0;
						while (mes->next != nullptr) {
							mes = mes->next;
							lcnt++;
						}
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 100; j++) {
							index = rand();
							deleteFromList(index,head,tail);
							lcnt--;
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t" << size << endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '7':
				oFile.open("listaPomiary/tabFind");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna\tRezultat" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateListInRange(size, head, tail, min, max);
					ElemList* mes = head;
					int lcnt = 0;
					while (mes->next != nullptr) {
						mes = mes->next;
						lcnt++;
					}
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						value = rand() % (lcnt);
						result = IsValueInList(value,head);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time << endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			};
		} while (opt != '0');
	}

	void ElemList::mesDisplay() {
		cout << "0 Wyjdz" << endl;
		cout << "1 Dodaj na poczatek" << endl;
		cout << "2 Dodaj na koniec" << endl;
		cout << "3 Dodaj z losowym indexem" << endl;
		cout << "4 Usun pierwszy indeks" << endl;
		cout << "5 Usun ostatni indeks" << endl;
		cout << "6 Usun losowy indeks" << endl;
		cout << "7 Znajdz wartosc" << endl;
	}

	void ElemList::generateListInRange(int size, ElemList*& head, ElemList*& tail, int min, int max) {
		ElemList* buf = head;
		while (head != nullptr) {
			buf = buf->next;
			delete head;
			head = buf;
		}
		//head = nullptr;
		tail = nullptr;
		int value = 0;
		for (int i = 0; i < size; i++) {
			value = rand();
			ElemList* elem = new ElemList;
			elem->data = value;
			elem->next = nullptr;
			if (head == nullptr) {
				head = elem;
				tail = elem;
				head->prev = nullptr;
			}
			else {
				tail->next = elem;
				tail->next->prev = tail;
				tail = elem;
			}
		}
	}
	void ElemList::addTail(int value, ElemList *&tail) {
		ElemList *node = new ElemList;
		tail->next = node;
		node->prev = tail;
		tail = node;
		node->data = value;
	}
	void ElemList::deleteHead(ElemList*& head, ElemList *&tail) {
		if (head != nullptr && head != tail) {
			ElemList* elem = head->next;
			delete head;
			head = elem;
			return;
		}
		if (head == tail) {
			delete head;
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
	}
	void ElemList::deleteTail(ElemList*& head, ElemList*& tail) {
		if (tail != nullptr && tail != head) {
			ElemList* elem = tail->prev;
			elem->next = nullptr;
			delete tail;
			tail = elem;
			return;
		}
		if (tail == head) {
			delete head;
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
	}