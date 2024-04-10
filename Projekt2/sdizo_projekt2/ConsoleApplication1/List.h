#pragma once
#include <list>
#include <vector>
#include<string>
#include "Amatrix.h"
using namespace std;
class List {
public:

	int edgeCnt;
	int nodeCnt;
	int param;
	list<pair<int,int>>* adjList;

	

	List();

	~List();

	void addEdge(int u, int v, int w);

	int loadFromFileMST(string FileName);
	
	int loadFromFileForMST(string FileName);

	float PrimAlgorithm();

	void deleteList();

	void printList();

	float Djikstra();

	float Kruskal();

	int FindSet(int* parent, int x);

	void Union(int x, int y, int* parent, int* rank);

	int generateUndirected(int** matrix, int nodes);

	int MinKey(int* key, bool* rozp);

	int generateDirected(int** matrix, int nodes);

	void SPmeasure(Amatrix matrix);

	void MSTmeasure(Amatrix matrix);
};