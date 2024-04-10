#include<iostream>
#include <string>
#include"Heap.h"
#include<fstream>
#include <conio.h>
#include<Windows.h>
using namespace std;

Heap::Heap() {

}
Heap::~Heap() {

}

int Heap::loadFromFile(string FileName) {
	if (heap != nullptr) {
		delete heap;
		heap = nullptr;
	}
	cout << "Wczytywanie kopca z pliku..." << endl;
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "Blad przy wczytywaniu pliku, nie odnaleziono pliku o zdanej nazwie" << endl;
		return 0;
	}
	int i_fromFile = 0;
	int* bufor;
	int it = 0;
	bufor = nullptr;
	heap = new int[5000000];
	cnt = 0;
	iFile >> it;					//it okreœla iloœæ liczb w pliku
	for (int k = 0; k < it; k++) {
		if (iFile >> i_fromFile) {
			heap[cnt] = i_fromFile;
			cnt++;
		}
		else {
			cout << "Nieprawidlowy format pliku, wczytano " << k << " wartosci" << endl;
		}

	}
	//tab = table;
	delete bufor;
	iFile.close();
	return 0;
}

bool Heap::isValueInHeap(int val) {		//algorytm usuwa korzeñ sprawdzaj¹c wczeœniej czy nie by³o w nim szukanego elementu, nastêpnie przywracane s¹ w³asnoœci kopca
	Heap kop;
	kop.heap = heap;
	kop.cnt = cnt;
	for (int i = 0; i < cnt; i++) {
		if (kop.heap[0] == val) {
			return true;
		}
		kop.deleteRoot();
	}
	return false;
}

void Heap::addValue(int val) {			//dodawanie do tablicy, po czym naprawienie kopca w razie potrzeby
	heap[cnt] = val;
	cnt++;
	fixHeapUp(cnt - 1);

}

void Heap::deleteFromHeap(int val) {	//usuniêcie z tablicy, po czym naprawienie kopca w razie potrzeby
	/*int index = 0;
	for (int i = 0; i < cnt; i++) {
		if (heap[i] == val) {
			index = i;
			for (int j = i; j < cnt; j++) {
				if (index == 0) {
					heap[0] = heap[cnt - 1];
					break;
				}
				heap[j] = heap[j + 1];
			}
		}
	}
	cnt--;
	for (int i = 0; i < cnt - 1; i++) {
		if (heap[i] < heap[2 * i + 1] || heap[i] < heap[2 * i + 2]) {
			fixHeapDown(i);
		}
	}*/
	int index = 0;
	for (int i = 0; i < cnt; i++) {
		if (heap[i] == val) {
			index = i;
			heap[index] = heap[cnt - 1];
			cnt--;
			break;
		}
	}
	fixHeapDown(index);
	//fixHeapUp(index);
}

void Heap::fixHeapDown(int index) {		//naprawa kopca w dó³
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int bufor;
	while ((heap[index] < heap[left]&&left<cnt) || (heap[index] < heap[right]&&right<cnt)) {
		if ((heap[left] > heap[right])&&left<cnt) {
			bufor = heap[left];
			heap[left] = heap[index];
			heap[index] = bufor;
			index = left;
		}
		if((heap[index]<heap[left]||heap[index]< heap[right])&&right<cnt) {
			bufor = heap[right];
			heap[right] = heap[index];
			heap[index] = bufor;
			index = right;
		}
		left = 2 * index + 1;
		right = 2 * index + 2;

	}
}

void Heap::fixHeapUp(int index) {							//naprawa kopca w górê
	int bufor;
	int parent = (int)((index - 1) / 2);
	while (heap[index] > heap[parent]) {
		bufor = heap[index];
		heap[index] = heap[parent];
		heap[parent] = bufor;
		index = parent;
		int parent = (int)((index - 1) / 2);
	}
}

void Heap::generateHeap(int size) {			
	if (heap != nullptr) {
		delete heap;
		heap = nullptr;
	}
	heap = new int[5000000];
	for (int i = 0; i < size; i++) {
		int val = rand();
		heap[i] = val;
	}
	cnt = size;
	//create_heap_dn();
}


void Heap::create_heap_dn() {						//tworzenie kopca metod¹ Floyda
	if (cnt > 0) {
		for (int i = (cnt - 1) / 2; i >= 0; i--) {	// wymagana naprawa od indeksu ostatniego rodzica
			heap_c_down(i);
		}
	}
}
void Heap::heap_c_down(int index) {			//naprawa kopca w dó³, od indeksu ostatniego rodzica sprawdzane s¹ warunki koca typu max(wartoœæ rodzica wiêksza od dzieci), w razie potrzeby naprawa
	if (cnt > 0) {
		int bufor = heap[index];
		int left_child_index = (int)(2 * index + 1);
		int right_child_index = (int)(2 * index + 2);
		int greater_child_index;
		if (heap[left_child_index] > heap[right_child_index]) {
			greater_child_index = left_child_index;
		}
		else {
			greater_child_index = right_child_index;
		}
		if (heap[greater_child_index] > bufor) {
			heap[index] = heap[greater_child_index];
			heap[greater_child_index] = bufor;
		}
	}
}
void Heap::deleteRoot() {											//funkcja u¿ywana w pomiarach, usuwa korzen
	heap[0] = heap[cnt - 1];
	cnt--;
	int index = 0;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	while (heap[index] < heap[left] || heap[index] < heap[right]) {
		if (index >= cnt) {
			break;
		}
		if (left > cnt || right > cnt) {
			break;
		}
		int greater;
		if (heap[left] > heap[right]) {
			if (left < cnt) {
				greater = heap[left];
				heap[left] = heap[index];
				heap[index] = greater;
				index = left;
			}
		}else{
			if (right < cnt) {
				greater = heap[right];
				heap[right] = heap[index];
				heap[index] = greater;
				index = right;
			}
		}
		left = 2 * index + 1;
		right = 2 * index + 2;
		if (left > cnt || right > cnt)
			break;

	}
	
}

bool Heap::check_heap() {
	for (int i = 0; i < cnt; i++) {
		int parent, left, right = 0;
		parent = heap[i];
		left = heap[2 * i + 1];
		right = heap[2 * i + 2];
		if (parent < left)
			return false;
		if (parent < right)
			return false;
	}
	return true;
}
void Heap::displayHeap(string sp, string sn, int curr) {
	//cr = "+--\n/";
	//cl = "/\n+--";
	//cp = "/\n/";
	string cr, cl, cp, s;
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;
	if (curr < cnt) {
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		displayHeap(s + cp, cr, 2*curr + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << heap[curr] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		displayHeap(s + cp, cl, 2 * curr + 1);
	}

}
void Heap::displayHeap_t() {
	int curr = 0;
	cout << "Kopiec:" << endl;
	cout << "[ ";
	while (curr < cnt) {
		cout << heap[curr] << " ";
		curr++;
	}
	cout << "]" << endl<<endl;
}

void Heap::heapMeasure(){
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
				//cout << "Prosze podac liczbe pomiarow: " << endl;
				mesCount = 10;
				//cin >> mesCount;
				while (size < 100) {
					cout << "Prosze podac rozmiar tablicy (wiêkszy ni¿ 100): " << endl;
					cin >> size;
				}
				min, max = 0;
				/*cout << "Prosze podac minimalna wartosc przechowywana w tablicy" << endl;
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
				}*/
			}
			fflush(stdin);
			switch (opt) {
			case '1':
				//dodawanie na poczatek:
				//--------zakres wartosci generowanych w tablicy 0-100
				oFile.open("kopiecPomiary/heapAdd");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateHeap(size);
					int r = rand();
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						addValue(r);
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
				oFile.open("kopiecPomiary/heapSub.");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				for (int i = 0; i < mesCount; i++) {
					generateHeap(size);
					int r;
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						deleteRoot();
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
				oFile.open("kopiecPomiary/heapSearch");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tIndeksRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				//cout << "dodawanie do losowego indexu" << endl;
				index = 0;
				for (int i = 0; i < mesCount; i++) {
					generateHeap(size);
					int r = rand();
					QueryPerformanceCounter(&startTime);
					for (int j = 0; j < 100; j++) {
						isValueInHeap(r);
					}
					QueryPerformanceCounter(&endTime);
					diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
					float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
					if (oFile.is_open()) {
						oFile << time <<  endl;
					}
					fflush(stdin);
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			case '4':
				oFile.open("kopiecPomiary/floydHeap");
				if (oFile.is_open()) {
					oFile << "";
					//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
				}
				if (mesCount > size) {
					cout << "Tablica jest zbyt mala do tej liczby pomiarow!!!" << endl;
				}
				else {
					for (int i = 0; i < mesCount; i++) {
						generateHeap(size);
						QueryPerformanceCounter(&startTime);
						for (int j = 0; j < 1; j++) {
							create_heap_dn();
						}
						QueryPerformanceCounter(&endTime);
						diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
						float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
						if (oFile.is_open()) {
							oFile << time << "\t" << size<< endl;
						}
						fflush(stdin);
					}
				}
				if (oFile.is_open()) {
					oFile.close();
				}
				break;
			/*case '5':
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
							deleteFromTable(cnt - 1);
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
				}*/
			/*case '6':
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
				}*/
			};
		} while (opt != '0');
}
void Heap::mesDisplay() {
	cout << "0 Wyjdz" << endl;
	cout << "1 Dodaj" << endl;
	cout << "2 Usun" << endl;
	cout << "3 znajdz" << endl;
	cout << "4 Tworzenie" << endl;
	//cout << "5 Usun ostatni indeks" << endl;
	//cout << "6 Usun losowy indeks" << endl;
	//cout << "7 Znajdz wartosc" << endl;
}
void Heap::deleteRoot(int iterations) {
	for (int i = 1; i < iterations; i++) {
		heap[i - 1] = heap[i];
	}
	cnt--;
	create_heap_dn();
}
