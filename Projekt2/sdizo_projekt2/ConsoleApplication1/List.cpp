#include"List.h"
#include<string>
#include<iostream>
#include<fstream>
#include<string.h>
#include<Windows.h>
#include <conio.h>
#include <queue>
#include<list>
using namespace std;
List::List(){}
List::~List(){}

void List::addEdge(int u, int v, int w) {
	adjList[u].push_back(make_pair(v, w));
}
void List::deleteList() {
	if (adjList != nullptr) {

		delete[] adjList;
		adjList = nullptr;
	}

}
int List::loadFromFileMST(string FileName) {
	deleteList();
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "nofile" << endl;
		return 1;
	}
	iFile >> edgeCnt;
	iFile >> nodeCnt;
	iFile >> param;
	int startNode;
	int endNode;
	adjList = new list<pair<int, int>>[nodeCnt];
	int val;
	for (int i = 0; i < edgeCnt; i++) {
		iFile >> startNode;
		iFile >> endNode;
		iFile >> val;
		addEdge(startNode,endNode,val);
	}
}

int List::loadFromFileForMST(string FileName) {
	deleteList();
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "nofile" << endl;
		return 1;
	}
	iFile >> edgeCnt;
	iFile >> nodeCnt;
	param = 0;
	int startNode;
	int endNode;
	int val;
	adjList = new list<pair<int, int>>[nodeCnt];
	for (int i = 0; i < edgeCnt; i++) {
		iFile >> startNode;
		iFile >> endNode;
		iFile >> val;
		addEdge(startNode,endNode, val);
		addEdge(endNode,startNode, val);
	} 
}

void List::printList() {
	cout << "Lista sasiedztwa" << endl;
	for (int i = 0; i < nodeCnt; ++i) {
		cout << i << ": ";
		for (const auto& edge : adjList[i]) {
			cout << "(" << edge.first << ", " << edge.second << ") ";
		}
		cout << endl;
	}
}

float List::Djikstra() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	if (adjList == nullptr) {
		return 1;
	}
	
	int lastnode = 0;
	int* d = new int[nodeCnt];
	int* p = new int[nodeCnt];
	int* visited = new int[nodeCnt];
	int* rozp = new int[nodeCnt];
	int visCnt = 0;
	vector<vector<int>> ADJ(nodeCnt);
	for (int i = 0; i < nodeCnt; i++) {
		d[i] = INT_MAX;
		p[i] = -1;
		rozp[i] = 0;
	}
	d[param] = 0;
	visited[visCnt] = param;
	visCnt++;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	for (int i = 0; i < nodeCnt; i++) {
		Q.push(make_pair(d[i], i));
	}
	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if (rozp[u] == 0) {
				for(const auto& vertex : adjList[u]){
					int v = vertex.first;
					if (d[v] > d[u] + vertex.second) {
						d[v] = d[u] + vertex.second;
						p[v] = u;
						Q.push(make_pair(d[v], v));
					}
				}
			rozp[u] = 1;
		}
	}
	QueryPerformanceCounter(&endTime);
	diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
	int cost = 0;
	//for (int i = 0; i < nodeCnt; i++) {
	//	cost = cost + d[i];
	//}
	p[param] = 0;
	vector<vector<int>> path;
	vector<int> nodePath;
	for (int i = 0; i < nodeCnt; i++) {
		nodePath.push_back(i);
		int j = i;
		int weigh = 0;
		int prevW = 0;
		//cout << i << ": ";
		weigh = d[i];
		while (1) {
			nodePath.push_back(p[j]);
			if (p[j] == 0) {
				break;
			}
			j = p[j];
		}
		//cout << weigh << endl;
		nodePath.push_back(weigh);
		path.push_back(nodePath);
		nodePath.clear();
		cout << endl;
	}
	for (int i = 0; i < nodeCnt; i++) {
		nodePath = path[i];
		int weigh = nodePath[nodePath.size() - 1];
		cout << i << ": ";
		int k = nodePath.size() - 2;
		while (k > 0) {
			cout << nodePath[k] << " ";
			k--;
			if (k < 0) {
				break;
			}
		}
		cout << i << "      |" << weigh << endl;
		//cout << endl;
	}
	return time;
}

float List::PrimAlgorithm() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	List mst;
	list<pair<int, int>>* mstList = nullptr;
	if (adjList == nullptr) {
		return 1;
	}
	int* key = new int[nodeCnt];
	int* p = new int[nodeCnt];
	int* rozp = new int[nodeCnt];
	int* nierozp = new int[nodeCnt];
	int nodesAdded = nodeCnt;
	mstList = new list<pair<int, int>>[nodeCnt];
	mst.adjList = mstList;
	for (int i = 0; i < nodeCnt; i++) {
		rozp[i] = 0;
		key[i] = INT_MAX;
		p[i] = -1;
	}
	key[0] = 0;
	p[0] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	for (int i = 0; i < nodeCnt; i++) {
		Q.push(make_pair(key[i], i));
	}
	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if (rozp[u] == 0) {
			for (const auto& vertex : adjList[u]) {
				int v = vertex.first;
				if (vertex.second < key[v] && rozp[v] == 0) {
					key[v] = vertex.second;
					p[v] = u;
					Q.push(make_pair(key[v], v));
				}///

				 //
			/*for (int i = 0; i < ADJ[u].size(); i++) {
				int v = ADJ[u][i];
				while (currElem != NULL) {
					currElem = currElem->next;
					if (currElem != nullptr) {
						if ((currElem->startNode == u && currElem->endNode == v) || (currElem->startNode == v && currElem->endNode == u)) {
							if (currElem->weigh < key[v]&&rozp[v]==0) {
								key[v] = currElem->weigh;
								p[v] = u;
								Q.push(make_pair(key[v], v));
							}
						}
					}
				}*/
			}
		}
		rozp[u] = 1;
	}
	QueryPerformanceCounter(&endTime);
	diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
	int sum = 0;
	for (int j = 0; j < nodeCnt; j++) {
		sum = sum + key[j];
		if (p[j] == -1) {
			p[j] = j;
		}
	}
	for (int i = 1; i < nodeCnt; i++) {
		mst.addEdge(i, p[i], key[i]);
		mst.addEdge(p[i],i,key[i]);

	}
	for (int i = 0; i < nodeCnt; ++i) {
		cout << i << ": ";
		for (const auto& edge : mstList[i]) {
			cout << "(" << edge.first << ", " << edge.second << ") ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Wartosc sumaryczna: " << sum << endl;
	return time;
}


float List::Kruskal() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	int sum = 0;
	List mstList;
	list<pair<int, int>>* mst = nullptr;
	if (adjList == nullptr) {
		return 1;
	}
	struct Kedge {
		int start;
		int end;
		int weigh;
		Kedge() {};
	};

	struct Compare {
		bool operator()(const Kedge& a, const Kedge& b) const {
			return a.weigh > b.weigh;
		}
	};
	priority_queue < Kedge, vector<Kedge>, Compare> sE;
	for (int i = 0; i < nodeCnt; i++) {
		for (const auto& vertex : adjList[i]) {
			Kedge edge;
			edge.start = i;
			edge.end = vertex.first;
			edge.weigh = vertex.second;
			sE.push(edge);
		}
	}
	mst = new list<pair<int, int>>[nodeCnt];
	mstList.adjList = mst;

	//makeset:
	int* parent = new int[nodeCnt];
	int* rank = new int[nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
	while (!sE.empty()) {
		Kedge edge;
		edge = sE.top();
		sE.pop();
		if (FindSet(parent, edge.start) != FindSet(parent, edge.end)) {
			mstList.addEdge(edge.start, edge.end, edge.weigh);
			mstList.addEdge(edge.end, edge.start, edge.weigh);
			sum = sum + edge.weigh;
			Union(edge.start, edge.end, parent, rank);
		}
	}
	QueryPerformanceCounter(&endTime);
	diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
	for (int i = 0; i < nodeCnt; ++i) {
		cout << i << ": ";
		for (const auto& edge : mst[i]) {
			cout << "(" << edge.first << ", " << edge.second << ") ";
		}
		cout << endl;
	}
	cout << "Sumaryczna waga: " << sum << endl;
	return time;

}
int List::FindSet(int* parent, int x) {
	if (parent[x] != x) {
		parent[x] = FindSet(parent, parent[x]);
	}

	return parent[x];
}
void List::Union(int x, int y, int* parent, int* rank) {
	int a = FindSet(parent, x);
	int b = FindSet(parent, y);
	if (rank[a] < rank[b]) {
		parent[a] = b;
	}
	else {
		parent[b] = parent[a];
	}
	if (rank[a] = rank[b]) {
		rank[a] = rank[a] + 1;
	}
}

int List::generateUndirected(int** matrix, int nodes) {
	deleteList();
	adjList = new list<pair<int, int>>[nodes];
	nodeCnt = nodes;
	edgeCnt = 0;
	param = 0;
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			if (matrix[i][j] != 0) {
				addEdge(i, j, matrix[i][j]);
				edgeCnt++;
			}
		}
	}

	return 0;
}

int List::generateDirected(int **matrix, int nodes) {
	deleteList();
	adjList = new list<pair<int, int>>[nodes];
	nodeCnt = nodes;
	edgeCnt = 0;
	param = 0;
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			if (matrix[i][j] != 0) {
				addEdge(i, j, matrix[i][j]);
				edgeCnt++;
			}
		}
	}

	return 0;
}

void List::SPmeasure(Amatrix matrix) {
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
	int* nodes = new int[7];
	int* p = new int[3];
	p[0] = 20;
	p[1] = 60;
	p[2] = 99;
	nodes[0] = 10;
	nodes[1] = 20;
	nodes[2] = 30;
	nodes[3] = 40;
	nodes[4] = 50;
	nodes[5] = 60;
	nodes[6] = 70;
	ofstream aFile, lFile;
	aFile.open("Pomiary/AL_Djikstra");
	if (aFile.is_open()) {
		aFile << "";
		aFile << "Czas operacji[ms]\tV\tGestosc" << endl;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int n = 0; n < 50; n++) {
				matrix.generateDirected(nodes[j], p[i]);
				generateDirected(matrix.matrix, nodes[j]);
				float time = Djikstra();
				if (aFile.is_open()) {
					aFile << time << "\t\t\t" << nodes[j] << "\t\t\t" << p[i] << endl;
				}
			}
		}
	}
	if (aFile.is_open()) {
		aFile.close();
	}
}

void List::MSTmeasure(Amatrix matrix) {
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
	int* nodes = new int[7];
	int* p = new int[3];
	p[0] = 20;
	p[1] = 60;
	p[2] = 99;
	nodes[0] = 10;
	nodes[1] = 20;
	nodes[2] = 30;
	nodes[3] = 40;
	nodes[4] = 50;
	nodes[5] = 60;
	nodes[6] = 70;
	ofstream aFile, bFile;
	aFile.open("Pomiary/Al_Prim");
	bFile.open("Pomiary/Al_Kruskal");
	if (aFile.is_open()) {
		aFile << "";
		aFile << "Czas operacji[ms]\tV\tGestosc" << endl;
	}
	if (bFile.is_open()) {
		aFile << "";
		aFile << "Czas operacji[ms]\tV\tGestosc" << endl;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int n = 0; n < 50; n++) {
				matrix.generateUndirected(nodes[j],p[i]);
				generateUndirected(matrix.matrix, nodes[j]);
				float time = PrimAlgorithm();
				if (aFile.is_open()) {
					aFile << time << "\t\t\t" << nodes[j] << "\t\t\t" << p[i] << endl;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int n = 0; n < 50; n++) {
				generateUndirected(matrix.matrix, nodes[j]);
				float time = Kruskal();
				if (bFile.is_open()) {
					bFile << time << "\t\t\t" << nodes[j] << "\t\t\t" << p[i] << endl;
				}
			}
		}
	}
	if (aFile.is_open()) {
		aFile.close();
	}
	if (bFile.is_open()) {
		bFile.close();
	}
}