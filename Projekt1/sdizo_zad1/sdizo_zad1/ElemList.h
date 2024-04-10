#include<iostream>
#include <string>
using namespace std;
class ElemList
{
public:
		int data;
		ElemList* next;
		ElemList* prev;

	ElemList(); //konstruktor-wywo³ywany automatycznie przy tworzeniu obieku
	~ElemList(); //destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	int loadFromFile(string FileName, ElemList *&head, ElemList *&tail);

	bool IsValueInList(int val, ElemList *head);

	void addValue(int index, int value, ElemList *&head, ElemList *&tail);

	void addTail(int value, ElemList*& tail);

	void deleteFromList(int index, ElemList*& head, ElemList*& tail);

	void display(ElemList *head, ElemList *tail);

	void generateList(int size, ElemList*& head, ElemList*& tail);

	void measure(ElemList*& head, ElemList*& tail);

	void deleteHead(ElemList *&head, ElemList *&tail);
	
	void deleteTail(ElemList*& head, ElemList*& tail);

	void mesDisplay();

	void generateListInRange(int size, ElemList*& head, ElemList*& tail, int min, int max);

};