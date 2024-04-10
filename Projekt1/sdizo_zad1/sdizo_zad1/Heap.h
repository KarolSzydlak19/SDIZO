#include<iostream>
#include <string>
using namespace std;
class Heap {
	
public:
	int* heap;
	int cnt;
	Heap();
	~Heap();

	int loadFromFile(string FileName);//

	bool isValueInHeap(int val);

	void fixHeapDown(int index);

	void fixHeapUp(int index);

	void addValue(int value);

	void deleteFromHeap(int value);

	void generateHeap(int size);

	void heap_c_down(int index);//

	void deleteRoot();//

	bool  check_heap();//

	void create_heap_dn();//

	void displayHeap(string sp, string sn, int curr);//

	void displayHeap_t();

	void deleteRoot(int iterations);

	void heapMeasure();

	void mesDisplay();

};
