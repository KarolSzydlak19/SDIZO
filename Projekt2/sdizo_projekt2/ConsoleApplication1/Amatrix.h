#pragma once
#include <string>
#include<iostream>
using namespace std;
class Amatrix 
{
public:
	int nodeCnt;
	int edgeCnt;
	int param;
	int** matrix;
	
	Amatrix();

	~Amatrix();

	int loadFromFileMST(string FileName);

	int loadFromFileForMST(string FileName);

	void printMatrix();

	float PrimAlgorithm();

	int MinKey(int* key, bool* rozp);

	float Kruskal();

	int FindSet(int *parent, int x);

	void Union(int x, int y, int* parent, int *rank);

	float Djikstra();

	int generateUndirected(int V, int P);

	int generateDirected(int V, int P);

	void SPmeasure();

	void MSTmeasure();

};