#include<iostream>
#include <string>
#include"BSTelem.h"
#include<fstream>
#include <conio.h>
#include<Windows.h>
using namespace std;

BSTelem::BSTelem() {

}
BSTelem::~BSTelem(){

}

int BSTelem::loadFromFile(string FileName) {
	cout << "Wczytywanie drzewa BST z pliku..." << endl;
	if (root != nullptr) {
		deleteBST(root);
		root = nullptr;
	}
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "Blad przy wczytywaniu pliku, nie odnaleziono pliku o zdanej nazwie" << endl;
		return 0;
	}
	int i_fromFile = 0;
	int iteration = 0;
	int* bufor;
	int it = 0;
	bufor = nullptr;
	iFile >> it;					//it okreœla iloœæ liczb w pliku
	for (int k = 0; k < it; k++) {
		if (iFile >> i_fromFile) {
			addValue(i_fromFile);
		}
	}
	//tab = table;
	iFile.close();
	return 0;
}
void BSTelem::addValue(int value) {	//dodanie
	node* elem = new node;
	node* currElem;
	node *currParent = nullptr;
	bool left = false;
	elem->data = value;
	if (root == nullptr) {			// jeœli drzewo jest puste wstawiamy korzeñ
		root = elem;
		elem->parent = nullptr;
		elem->right = nullptr;
		elem->left = nullptr;
		return;
	}
	else {
		currElem = root;
		currParent = root;
		while (currElem != nullptr) {				// jeœli drzewo nie jest puste dodajemy nie zaburzaj¹c w³asnoœci BST, pêtla iteruje po kolejnych wêz³ach do momentu w którym
			if (elem->data <= currElem->data) {		// mo¿na dodaæ wartoœæ do BST nie zaburaj¹c jego w³asnoœci
				currElem = currElem->left;
				if (currParent->left != nullptr) {
					currParent = currParent->left;
				}
				left = true;
			}
			else {
				currElem = currElem->right;
				if (currParent->right != nullptr) {
					currParent = currParent->right;
				}
				left = false;
			}
		}
		elem->parent = currParent;
		if (left == true) {
			currParent->left = elem;
		}
		else {
			currParent->right = elem;
		}
		elem->right = nullptr;
		elem->left = nullptr;
	}
	
}
BSTelem::node* BSTelem::findPredecessor(node* elem) {	//funkcja szuka poprzednika
	if (elem->left != nullptr) {						//przypadek 1 wêze³ posiada lewego potomka (poprzednikiem jest maksymalna wartoœæ w tym poddrzewie)
		elem = elem->left;
		while (elem->right != nullptr) {
			elem = elem->right;
		}
		return elem;
	}
	if (elem->left == nullptr) {						//brak lewego potomka szukanie pierwszego ojca dla którego wêze³ le¿y w prawym poddrzewie
		node* prev = elem;
		if (elem == root) {								//jeœli drzewo zawiera 1 element zwracany kest wskaŸnik na korzeñ, wyj¹tek obs³u¿ony w funkcji wywo³uj¹cej
			return elem;
		}
		elem = elem->parent;
		while (elem->right != prev) {
			if (elem == root) {
				break;
			}
			prev = prev->parent;
			elem = elem->parent;
		}
	}
	return elem;
}
BSTelem::node* BSTelem::findSuccessor(node* elem) {		// funkcja szuka nastêpnika, analogicznie do findPredecessor
	if (elem->right != nullptr) {
		elem = elem->right;
		while (elem->left != nullptr) {
			elem = elem->left;
		}
		return elem;
	}
	if (elem->right == nullptr) {
		node* prev = elem;
		elem = elem->parent;
		if (elem != nullptr) {
			while (elem->right != prev) {
				prev = prev->parent;
				elem = elem->parent;
				if (elem == root) {
					break;
				}
			}
		}
		else {
			return nullptr;
		}
	}
	return elem;
}
void BSTelem::deleteFromBST(node *&root, int value) {			//usuwanie
	node* elem = root;
	node* parent;
	node* suc;
	while (elem->data != value) {
		if (elem->data > value) {
			elem = elem->left;
		}
		else {
			elem = elem->right;
		}
		if (elem == nullptr) {
			return;
		}
	}
	if (elem->right == nullptr && elem->left == nullptr) {		// wêze³ jest liœciem 
		parent = elem->parent;
		if (parent == nullptr) {
			return;
		}
		if (parent->right == elem) {
			parent->right = nullptr;
		}
		else {
			parent->left = nullptr;
		}
		delete elem;
		return;
	}
	if (elem->right == nullptr || elem->left == nullptr) {		//wêze³ posiada jednego potomka
		parent = elem->parent;
		if (parent != nullptr) {
			if (parent->right == elem) {
				if (elem->right == nullptr) {
					parent->right = elem->left;
					elem->left->parent = parent;
				}
				else {
					parent->right = elem->right;
					elem->right->parent = parent;
				}
			}
			else {
				if (elem->right == nullptr) {
					parent->left = elem->left;
					elem->left->parent = parent;
				}
				else {
					parent->left = elem->right;
					elem->right->parent = parent;
				}
			}
		}
		else {
			suc = elem->left;
			if (suc == nullptr) {
				return;
			}
			suc -> parent = nullptr;
			root = suc;
		}
		delete elem;
		return;
	}
	suc = findSuccessor(elem);			// wêze³ posiada dwóch potomków
	cout << suc->data << endl;
	elem->data = suc->data;
	parent = suc->parent;
	if (parent->left == suc) {
		parent->left = suc->left;
	}if(parent->right==suc){
			parent->right = suc->right;
	}
	delete suc;
	return;
}
bool BSTelem::IsValueInBST(int value) {	//przeszukiwanie drzewa
	node* elem = root;
	while (elem->data != value) {
		if (value < elem->data) {
			elem = elem->left;
		}
		else {
			elem = elem->right;
		}
		if (elem == nullptr) {
			return false;
		}
	}
	return true;
}
void BSTelem::display(string sp, string sn, node *node) {
	string cr, cl, cp, s;
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;
	if (node) {
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		display(s + cp, cr, node->right);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << node->data << endl;

		s = sp;
		if (sn == cl)s[s.length() - 2] = ' ';
		display(s + cp, cl, node->left);
	}
}
void BSTelem::rotateRight(node*& A) {		//rotacja w prawo
	if (A->left == nullptr) {
		return;
	}
	A->left->parent = A->parent;
	if (A->parent == nullptr) {
		root = A->left;
	}
	A->parent = A->left;
	if (A->left->right != nullptr) {
		A->left->right->parent = A;
	}
	A->left = A->left->right;
	if (root != A->parent) {
		if (A->parent->parent->right == A) {
			A->parent->parent->right = A->parent;
		}
		else {
			A->parent->parent->left = A->parent;
		}
	}
	A->parent->right = A;
}
void BSTelem::rotateLeft(node*& A) {		// rotacja w lewo
	if (A->right == nullptr) {
		return;
	}
	A->right->parent = A->parent;
	if (A->parent == nullptr) {
		root = A->right;
	}
	A->parent = A->right;
	if (A->right->left != nullptr) {
		A->right->left->parent = A;
	}
	A->right = A->right->left;
	if (root != A->parent) {
		if (A->parent->parent->left == A) {
			A->parent->parent->left = A->parent;
		}
		else {
			A->parent->parent->right = A->parent;
		}
	}
	A->parent->left = A;

}
void BSTelem::CreateLinear() {			//pierwsza czêsæ algorytmu DSW, prostowanie drzewa
	node* tmp = root;
	node* r = root;
	while (tmp != nullptr) {
		if (tmp->left != nullptr) {
			rotateRight(tmp);
			tmp = tmp->parent;
			if (tmp->parent == nullptr) {
				root = tmp;
			}
		}
		else {
			tmp = tmp->right;
		}
		if (tmp != nullptr) {
			//cout <<"tmp"<< tmp->data << endl;
		}
	}
}
void BSTelem::CreateBalancedTree() {				//algorytm DSW czêœæ 2 równowa¿enie
	node* tmp;
	tmp = root;
	int n = 0;
	while (tmp != nullptr) {
		n++;
		tmp = tmp->right;
	}
	tmp = root;
	int m = pow(2, int(log2(n + 1))) - 1;
	node** nodeTab;
	int rotations = n - m;
	nodeTab = new node * [rotations];
	for (int i = 0; i < rotations; i++) {
		nodeTab[i] = tmp;
		if (tmp->right->right == nullptr) {
			break;
		}
		tmp = tmp->right->right;
	}
	for (int i = 0; i < rotations; i++) {
		rotateLeft(nodeTab[i]);
	}
	delete nodeTab;
	while (m > 1) {
		m = int(m / 2);
		tmp = root;
		nodeTab = new node * [m];
		for (int i = 0; i < m; i++) {
			nodeTab[i] = tmp;
			if (tmp->right->right == nullptr) {
				break;
			}
			tmp = tmp->right->right;
		}
		for (int i = 0; i < m; i++) {
			rotateLeft(nodeTab[i]);
		}
		delete nodeTab;
	}
}
void BSTelem::DSW() {
	CreateLinear();
	CreateBalancedTree();
}

void BSTelem::generateBST(int size) {
	if (root != nullptr) {
		deleteBST(root);
		root = nullptr;
	}
	for (int i = 0; i < size; i++) {
		int r = rand();
		addValue(r);
	}
}

void BSTelem::deleteBST(node*& elem) {			//funkcja usuwa ca³e drzewo BST
	if (elem == nullptr) {
		return;
	}
	deleteBST(elem->left);
	deleteBST(elem->right);
	delete elem;
}
void BSTelem::measureBST() {					//POMIARY
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
			mesCount = 10;
			cout << "Rozmiar?" << endl;
			cin >> size;

		}
		fflush(stdin);
		switch (opt) {
		case '1':
			//dodawanie na poczatek:
			//--------zakres wartosci generowanych w tablicy 0-100
			oFile.open("bstPomiary/BSTADD");
			if (oFile.is_open()) {
				oFile << "";
				//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
			}
			for (int i = 0; i < mesCount; i++) {
				generateBST(size);
				value = rand();
				QueryPerformanceCounter(&startTime);
				for (int j = 0; j < 500; j++) {
					addValue(value);
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
			oFile.open("bstPomiary/delBST");
			if (oFile.is_open()) {
				oFile << "";
				//oFile << "Czas operacji[ms]\tRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
			}
			for (int i = 0; i < mesCount; i++) {
				generateBST(size);
				int rootVAL;
				QueryPerformanceCounter(&startTime);
				for (int j = 0; j < 100; j++) {
					rootVAL = root->data;
					deleteFromBST(root, rootVAL);
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
			break;
		case '3':
			oFile.open("bstPomiary/searchBST");
			if (oFile.is_open()) {
				oFile << "";
				//oFile << "Czas operacji[ms]\tIndeksRozmiar\tWartosc minimalna\t Wartosc maksymalna" << endl;
			}
			cout << "dodawanie do losowego indexu" << endl;
			index = 0;
			for (int i = 0; i < mesCount; i++) {
				generateBST(size);
				int r = rand();
				QueryPerformanceCounter(&startTime);
				for (int j = 0; j < 100; j++) {
					IsValueInBST(r);
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
		/*case '4':
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
						deleteHead(head, tail);
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
						deleteFromList(index, head, tail);
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
					result = IsValueInList(value, head);
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
			break;*/
		};
	} while (opt != '0');
}
void BSTelem::mesDisplay() {
	cout << "0 Wyjdz" << endl;
	cout << "1 Dodaj " << endl;
	cout << "2 Usun" << endl;
	cout << "3 Przeszukaj" << endl;
	//cout << "4 Usun pierwszy indeks" << endl;
	//cout << "5 Usun ostatni indeks" << endl;
	//cout << "6 Usun losowy indeks" << endl;
	//cout << "7 Znajdz wartosc" << endl;
}